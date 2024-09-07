#pragma once
#include <string>
#include <mono/jit/jit.h>
class Mono
{
public:
	Mono();
	void Init(std::string libPath, std::string gameAssemblyFilePath);
private:
	MonoDomain* rootDomain;
	MonoDomain* appDomain;
};