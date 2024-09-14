#pragma once

#include <unordered_map>
#include <filesystem>
#include <string>

using namespace std;

class ShaderInfo
{
	public:
		ShaderInfo(filesystem::path& vertexPath, filesystem::path& fragmentPath,
			string& name);

		void AddPaths(filesystem::path& vertexPath, filesystem::path& fragmentPath);
		string GetName();

		filesystem::path GetPath(string name);

	private:
		unordered_map<string, filesystem::path> _paths;
		string _name;
};
