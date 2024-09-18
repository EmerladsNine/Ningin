#include "mono.h"
#include <mono/metadata/assembly.h>
#include <mono/metadata/mono-debug.h>
#include <stdexcept>
#include <iostream>
#include "InternalCalls.h"
#include "../../environment.h"
#include "../../math/vector2.h"
#include "../../utills/FileReader.h"
#include "../../utills/Debug.h"

Mono::Mono() : assembliesDirectory(Environment::GetGameDirectory()), _rootDomain(nullptr), _appDomain(nullptr)
	,gameAssembly(nullptr), ninginAssembly(nullptr) {}

Mono::~Mono()
{
	if (_appDomain != nullptr)
	{
		mono_jit_cleanup(_appDomain);
	}

	if (_rootDomain != nullptr)
	{
		mono_jit_cleanup(_rootDomain);
	}
}

void Mono::Init(string libPath, string gameAssemblyFileName, bool loadPDB)
{
	
	// Set the path for dotnet assemblies
	mono_set_assemblies_path(libPath.c_str());

	// Initialize Mono JIT Runtime.
	if (loadPDB)
	{
		std::vector<const char*> arguments;
		arguments.push_back("--debugger-agent=transport=dt_socket,address=127.0.0.1:2550,server=y,suspend=n,loglevel=3,logfile=MonoDebugger.log");
		arguments.push_back("--soft-breakpoints");
		mono_jit_parse_options(static_cast<int>(arguments.size()), const_cast<char**>(arguments.data()));
		mono_debug_init(MONO_DEBUG_FORMAT_MONO);
	}

	_rootDomain = mono_jit_init("NinginJITRuntime");
	if (_rootDomain == nullptr)
	{
		throw runtime_error("failed to init mono, couldn't get root domain");
	}

	//Initialise for debugging.
	if (loadPDB)
	{
		mono_debug_domain_create(_rootDomain);
	}
	
	// Create Mono App Domain.
	_appDomain = mono_domain_create_appdomain((char*)"NinginScriptRuntime", nullptr);
	if (_appDomain == nullptr)
	{
		throw runtime_error("failed to init mono, couldn't get app domain");
	}

	// Force set the created app domain as the current one.
	if (mono_domain_set(_appDomain, 1) == 0)
	{
		throw runtime_error("failed to set app domain");
	}

    // Link C# Managed Functions To C++ UnManaged Functions.
	AddInternalCalls();

    //Load Needed Assemblies.
	ninginAssembly = LoadAssembly(NINGIN_ASSEMBLY_NAME, loadPDB);
	gameAssembly = LoadAssembly(gameAssemblyFileName, loadPDB);
}

MonoAssembly* Mono::LoadAssembly(string fileName, bool loadPDB)
{
    //Check If Mono is initialized properly.
    if (_rootDomain == nullptr || _appDomain == nullptr)
    {
        throw runtime_error("Failed To Load Assembly : "+fileName+" , Mono Isn't Initialized !");
    }

    //Read Assembly File.
	filesystem::path assemblyPath = assembliesDirectory / fileName;
	if (!std::filesystem::exists(assemblyPath))
	{
		LogError("File Path Doesn't Exist :" + assemblyPath.string());
		return nullptr;
	}

	vector<uint8_t> dataVec = FileReader::ReadFileBytes(assemblyPath.string());
	char* data = reinterpret_cast<char*>(dataVec.data());

	MonoImageOpenStatus status;
	MonoImage* image = mono_image_open_from_data_full(data, static_cast<uint32_t>(dataVec.size()),
		1, &status, 0);

	if (status != MONO_IMAGE_OK)
	{
		const char* error = mono_image_strerror(status);
		LogError(std::string("Failed to load dll file image : " + assemblyPath.string() + ", error :") + error);
		return nullptr;
	}

	MonoAssembly* assembly = mono_assembly_load_from_full(image, assemblyPath.string().c_str(), &status, 0);
	mono_image_close(image);

	if (status != MONO_IMAGE_OK)
	{
		const char* error = mono_image_strerror(status);
		LogError(std::string("Failed to load dll file : "+assemblyPath.string()+", error :") + error);
		return nullptr;
	}
	LogInfo("Loaded dll file :" + assemblyPath.string());

	//Load Debuggig File
	if (loadPDB)
	{
		std::filesystem::path pdbPath = assemblyPath;
		pdbPath.replace_extension(".pdb");
		if (!std::filesystem::exists(pdbPath))
		{
			LogWarning("PDB file doesn't exist :" + pdbPath.string());
			return assembly;
		}

		vector<uint8_t> pdbFileDataVec = FileReader::ReadFileBytes(pdbPath.string());
		mono_debug_open_image_from_memory(image, (const mono_byte*)pdbFileDataVec.data(), static_cast<int>(pdbFileDataVec.size()));
		LogInfo("Loaded pdb file :"+pdbPath.string());
	}

	return assembly;
}

Script* Mono::GetScript(string scritpName)
{
	auto it = loadedClasses.find(scritpName);
	if (it != loadedClasses.end())
	{
		return BuildScript(&it->second);
	}
	else
	{
		//Script is not loaded.
		ScriptClass* scriptClass = LoadScript(scritpName);
		return BuildScript(scriptClass);
	}
}

Script* Mono::BuildScript(ScriptClass* scriptClass)
{
	MonoObject* obj = mono_object_new(_appDomain, scriptClass->klass);
	return new Script(scriptClass, obj);
}

ScriptClass* Mono::LoadScript(string scriptFullName)
{
	auto dotPos = scriptFullName.find('.');
	if (dotPos == string::npos)
	{
		throw invalid_argument("Invalid script name format.");
	}

	//Split FullName : "namespace.classname"
	string nameSpace = scriptFullName.substr(0, dotPos);
	string className = scriptFullName.substr(dotPos + 1);

	//Load the class.
	MonoImage* image = mono_assembly_get_image(gameAssembly);
	MonoClass* klass = mono_class_from_name(image, nameSpace.c_str(), className.c_str());

	auto [iter, inserted] = loadedClasses.emplace(scriptFullName, ScriptClass(klass));
	if (!inserted)
	{
		// Handle case where the script class already exists in the map
		return &iter->second;
	}

	InitScriptMethods(&iter->second);
	return &iter->second;
}

void InitScriptMethods(ScriptClass* scriptClass)
{
	scriptClass->startMethod = GetMethod(scriptClass->klass, "Start", 0);
	scriptClass->updateMethod = GetMethod(scriptClass->klass, "Update", 1);
	scriptClass->lateUpdateMethod = GetMethod(scriptClass->klass, "Late_Update", 1);
	scriptClass->destroyMethod = GetMethod(scriptClass->klass, "Destroy", 0);
}

MonoMethod* GetMethod(MonoClass* klass, string name, int paramsCount)
{
	return mono_class_get_method_from_name(klass, name.c_str(), paramsCount);
}

void* InvokeMethod(MonoObject* obj, MonoMethod* method,vector<void*> params)
{
	MonoObject* exception = nullptr;

	//Invoke Method
	MonoObject* result = mono_runtime_invoke(method, obj, params.data(), &exception);

	//Handle Exceptions.
	if (exception != nullptr)
	{
		MonoString* excp_str = mono_object_to_string(exception, nullptr);
		char* excep_cstr = mono_string_to_utf8(excp_str);
		string error_message = "Mono exception: ";
		error_message += excep_cstr;

		mono_free(excep_cstr);
		LogError(error_message);
	}

	//Unbox result to void*.
	if (result != nullptr)
	{
		return mono_object_unbox(result);
	}

	return nullptr;
}
