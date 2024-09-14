#pragma once

#include "string"

using namespace std;

struct MonoPaths
{
	public:
		MonoPaths(string monoPath, string gameAssemblyFileName);

		string monoPath;
		string gameAssemblyFileName;
};
