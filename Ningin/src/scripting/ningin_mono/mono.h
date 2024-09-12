#pragma once
#include <mono/jit/jit.h>
#include <filesystem>
#include <string>
#include <unordered_map>
#include "script_class.h"
#include "script.h"

class Mono
{
  public:
    const std::string NINGIN_ASSEMBLY_NAME = "NinginCore.dll";
    std::filesystem::path assembliesDirectory;
    MonoAssembly* ninginAssembly;
    MonoAssembly* gameAssembly;
    std::unordered_map<std::string, ScriptClass> loadedClasses;
    Mono();
    void Init(std::string libPath, std::string gameAssemblyFileName);
    MonoAssembly* LoadAssembly(std::string fileName);
    Script* GetScript(std::string scritpName);
    Script* BuildScript(ScriptClass* scriptClass);
    ScriptClass* LoadScript(std::string scriptFullName);
  private:
    MonoDomain *rootDomain;
    MonoDomain *appDomain;
};

void InitScriptMethods(ScriptClass* scriptClass);
MonoMethod* GetMethod(MonoClass* klass, std::string name, int paramsCount);