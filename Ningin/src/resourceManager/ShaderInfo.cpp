#include "ShaderInfo.h"

ShaderInfo::ShaderInfo(const filesystem::path vertexPath, const  filesystem::path fragmentPath,
	 string name) : _name(name)
{
	AddPaths(vertexPath, fragmentPath);
}

void ShaderInfo::AddPaths(const filesystem::path& vertexPath, const filesystem::path& fragmentPath)
{
	_paths["vertex"] = vertexPath;
	_paths["fragment"] = fragmentPath;
}

string ShaderInfo::GetName() 
{
	return _name;
}

const filesystem::path ShaderInfo::GetPath(string name) 
{
	return _paths.at(name);
}
