#pragma once

#include <unordered_map>
#include <filesystem>
#include <string>

using namespace std;

class ShaderInfo
{
	public:
		ShaderInfo(const filesystem::path vertexPath, const filesystem::path fragmentPath,
			string name);

		void AddPaths(const filesystem::path& vertexPath, const filesystem::path& fragmentPath);
		string GetName();

		const filesystem::path GetPath(string name);

	private:
		unordered_map<string, filesystem::path> _paths;
		string _name;
};
