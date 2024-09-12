#pragma once

#include <unordered_map>
#include <filesystem>
#include <string>

class ShaderInfo
{
	public:
		ShaderInfo(std::filesystem::path& vertexPath, std::filesystem::path& fragmentPath,
			std::string& name);

		void AddPaths(std::filesystem::path& vertexPath, std::filesystem::path& fragmentPath);
		std::string GetName();
		std::filesystem::path GetPath(std::string name);

	private:
		std::unordered_map<std::string, std::filesystem::path> paths;
		std::string name;
};
