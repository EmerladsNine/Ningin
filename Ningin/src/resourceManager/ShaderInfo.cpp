#include "ShaderInfo.h"

ShaderInfo::ShaderInfo( std::filesystem::path& vertex_path,  std::filesystem::path& fragment_path,
	 std::string& name) : name(name)
{
	AddPaths(vertex_path, fragment_path);
}

void ShaderInfo::AddPaths( std::filesystem::path& vertex_path,  std::filesystem::path& fragment_path)
{
	paths["vertex"] = vertex_path;
	paths["fragment"] = fragment_path;
}

std::string ShaderInfo::GetName() 
{
	return name;
}

std::filesystem::path ShaderInfo::GetPath(std::string name) 
{
	return paths.at(name);
}
