#include "mono.h"
#include <mono/metadata/assembly.h>
#include <stdexcept>
#include <iostream>
#include "internal_calls.h"
#include "../../environment.h"
#include "../../math/vector2.h"
#include "../../utills/file_reader.h"

Mono::Mono() : assembliesDirectory(Enironment::GetGameDirectory()) , rootDomain(nullptr) , appDomain(nullptr) ,gameAssembly(nullptr) , ninginAssembly(nullptr) 
{

}

void Mono::Init(std::string libPath, std::string gameAssemblyFileName)
{
	// Set the path for dotnet assemblies
	mono_set_assemblies_path(libPath.c_str());

	// Initialize Mono JIT Runtime.
	rootDomain = mono_jit_init("NinginJITRuntime");
	if (rootDomain == nullptr)
	{
		throw std::runtime_error("failed to init mono, couldn't get root domain");
	}

	// Create Mono App Domain.
	appDomain = mono_domain_create_appdomain((char*)"NinginScriptRuntime", nullptr);
	if (appDomain == nullptr)
	{
		throw std::runtime_error("failed to init mono, couldn't get app domain");
	}

	// Force set the created app domain as the current one.
	if (mono_domain_set(appDomain, 1) == 0)
	{
		throw std::runtime_error("failed to set app domain");
	}

    // Link C# Managed Functions To Rust UnManaged Functions.
	AddInternalCalls();

    //Load Needed Assemblies.
	ninginAssembly = LoadAssembly(NINGIN_ASSEMBLY_NAME);
	gameAssembly = LoadAssembly(gameAssemblyFileName);
}

MonoAssembly* Mono::LoadAssembly(std::string fileName)
{
    //Check If Mono is initialized properly.
    if (rootDomain == nullptr || appDomain == nullptr)
    {
        throw std::runtime_error("Failed To Load Assembly : "+fileName+" , Mono Isn't Initialized !");
    }

    //Read Assembly File.
	std::filesystem::path assemblyPath = assembliesDirectory / fileName;
	std::vector<uint8_t> data_vec = FileReader::ReadFileBytes(assemblyPath.string());
	char* data = reinterpret_cast<char*>(data_vec.data());

	MonoImageOpenStatus status;
	MonoImage* image = mono_image_open_from_data_full(data, data_vec.size(), 1, &status, 0);

	if (status != MONO_IMAGE_OK)
	{
		const char* error = mono_image_strerror(status);
		std::cerr << "Error: " << error << std::endl;
		return nullptr;
	}

	MonoAssembly* assembly = mono_assembly_load_from_full(image, assemblyPath.string().c_str(), &status, 0);
	mono_image_close(image);

	if (status != MONO_IMAGE_OK)
	{
		const char* error = mono_image_strerror(status);
		std::cerr << "Error: " << error << std::endl;
		return nullptr;
	}

	return assembly;
}

Script Mono::GetScript(std::string scritpName)
{
	auto it = loadedClasses.find(scritpName);
	if (it != loadedClasses.end())
	{
		return BuildScript(&it->second);
	}
	else
	{
		ScriptClass* scriptClass = LoadScript(scritpName);
		BuildScript(scriptClass);
	}
}

Script Mono::BuildScript(ScriptClass* scriptClass)
{
	MonoObject* obj = mono_object_new(appDomain, scriptClass->klass);
	return Script(scriptClass, obj);
}

ScriptClass* Mono::LoadScript(std::string scriptFullName)
{
	auto dotPos = scriptFullName.find('.');
	if (dotPos == std::string::npos) {
		throw std::invalid_argument("Invalid script name format.");
	}

	std::string nameSpace = scriptFullName.substr(0, dotPos);
	std::string className = scriptFullName.substr(dotPos + 1);

	MonoImage* image = mono_assembly_get_image(gameAssembly);
	MonoClass* klass = mono_class_from_name(image, nameSpace.c_str(), className.c_str());

	auto [iter, inserted] = loadedClasses.emplace(scriptFullName, ScriptClass(klass));
	if (!inserted) {
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

MonoMethod* GetMethod(MonoClass* klass, std::string name, int paramsCount)
{
	return mono_class_get_method_from_name(klass, name.c_str(), paramsCount);
}
