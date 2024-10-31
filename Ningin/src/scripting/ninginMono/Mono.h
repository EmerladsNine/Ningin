#pragma once

#include <mono/jit/jit.h>
#include <filesystem>
#include <string>
#include <unordered_map>
#include <functional>
#include "../../sceneSystem/ecs/EntityManager.h"
#include "../../sceneSystem/entity/EntityId.h"
#include "ScriptClass.h"
#include "Script.h"

using namespace std;

class Mono
{
      public:
        Mono();
        ~Mono();

        void Init(string libPath, string gameAssemblyFileName,bool loadPDB);

        static unordered_map<MonoType*, std::function<bool(EntityId, EntityManager&)>> HasComponent;
        static unordered_map<MonoType*, std::function<void*(EntityId, EntityManager&)>> GetComponent;
        template <typename T> MonoType* GetComponentManagedType()
        {
            const string_view mangledName = typeid(T).name();
            size_t pos = mangledName.find_last_of(":");
            if (pos == std::string::npos)
            {
                pos = mangledName.find_last_of(" ");
            }
            std::string_view className = mangledName.substr(pos + 1);
            std::string managedTypeName = format("NinginCore.{}", className);

            return mono_reflection_type_from_name(managedTypeName.data(), ninginAssemblyImage);
        }

        MonoAssembly* LoadAssembly(string fileName, bool loadPDB);

        Script* GetScript(EntityId entityId, string scritpName);
        Script* BuildScript(EntityId entityId, ScriptClass* scriptClass);
        ScriptClass* LoadScript(string scriptFullName, MonoAssembly* assembly);
        MonoClass* LoadClass(string scriptFullName, MonoAssembly* assembly);
        MonoString* GetMonoString(const char* text);

        const string NINGIN_ASSEMBLY_NAME = "NinginCore.dll";
        filesystem::path assembliesDirectory;

        MonoAssembly* ninginAssembly;
        MonoImage* ninginAssemblyImage;
        MonoAssembly* gameAssembly;

        unordered_map<string, ScriptClass> loadedClasses;
        MonoClass* entityClass;
        MonoMethod* entityConstructor;

      private:
        MonoDomain *_rootDomain;
        MonoDomain *_appDomain;
};

void InitScriptMethods(ScriptClass* scriptClass);

MonoMethod* GetMethod(MonoClass* klass, string name, int paramsCount);

void* InvokeMethod(MonoObject* obj, MonoMethod* method, vector<void*> params);