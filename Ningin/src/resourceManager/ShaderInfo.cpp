#include "ShaderInfo.h"

ShaderInfo::ShaderInfo(filesystem::path& vertexPath, filesystem::path& fragmentPath,
	 string& name) : _name(name)
{
	AddPaths(vertexPath, fragmentPath);
}

void ShaderInfo::AddPaths(filesystem::path& vertexPath, filesystem::path& fragmentPath)
{
	_paths["vertex"] = vertexPath;
	_paths["fragment"] = fragmentPath;
}

string ShaderInfo::GetName() 
{
	return _name;
}

filesystem::path ShaderInfo::GetPath(string name) 
{
	return _paths.at(name);
}
