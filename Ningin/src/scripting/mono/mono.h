#pragma once
#include <mono/jit/jit.h>
#include <string>
class Mono
{
  public:
    Mono();
    void Init(std::string libPath, std::string gameAssemblyFilePath);

  private:
    MonoDomain *rootDomain;
    MonoDomain *appDomain;
};
