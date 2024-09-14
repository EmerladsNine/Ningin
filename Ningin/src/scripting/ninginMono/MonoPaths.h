#pragma once
#include "string"

struct MonoPaths
{
public:
	MonoPaths(std::string monoPath, std::string gameAssemblyFileName);
	std::string monoPath;
	std::string gameAssemblyFileName;
};
