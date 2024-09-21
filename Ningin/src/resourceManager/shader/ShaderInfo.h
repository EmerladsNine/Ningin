#pragma once

#include <unordered_map>
#include <filesystem>
#include <string>

using namespace std;

class ShaderInfo
{
	public:
		ShaderInfo(string name, const filesystem::path& vertexPath, const filesystem::path& fragmentPath,
			const filesystem::path* geometryPath = nullptr);

		void AddPaths(const filesystem::path& vertexPath, const filesystem::path& fragmentPath,
			const filesystem::path* geometryPath);

		string GetName();

		const filesystem::path GetPath(const string& name);
		const filesystem::path* GetOptionalShaderPath(const string& name);

	private:
		unordered_map<string, filesystem::path> _paths;
		const filesystem::path* _geometryPath;
		string _name;
};
