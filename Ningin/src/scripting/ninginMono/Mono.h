#pragma once

#include <mono/jit/jit.h>
#include <filesystem>
#include <string>
#include <unordered_map>
#include "ScriptClass.h"
#include "Script.h"

using namespace std;

class Mono
{
      public:
        Mono();
        ~Mono();

        void Init(string libPath, string gameAssemblyFileName,bool loadPDB);

        MonoAssembly* LoadAssembly(string fileName, bool loadPDB);

        Script* GetScript(string scritpName);
        Script* BuildScript(ScriptClass* scriptClass);
        ScriptClass* LoadScript(string scriptFullName);
        MonoString* GetMonoString(const char* text);

        const string NINGIN_ASSEMBLY_NAME = "NinginCore.dll";
        filesystem::path assembliesDirectory;

        MonoAssembly* ninginAssembly;
        MonoAssembly* gameAssembly;

        unordered_map<string, ScriptClass> loadedClasses;

      private:
        MonoDomain *_rootDomain;
        MonoDomain *_appDomain;
};

void InitScriptMethods(ScriptClass* scriptClass);

MonoMethod* GetMethod(MonoClass* klass, string name, int paramsCount);

void* InvokeMethod(MonoObject* obj, MonoMethod* method, vector<void*> params);