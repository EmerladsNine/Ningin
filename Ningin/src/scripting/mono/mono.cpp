#include "mono.h"
#include <mono/metadata/assembly.h>
#include <stdexcept>

void Mono::Init(std::string libPath, std::string gameAssemblyFilePath)
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
    appDomain = mono_domain_create_appdomain((char *)"NinginScriptRuntime", nullptr);
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
}
