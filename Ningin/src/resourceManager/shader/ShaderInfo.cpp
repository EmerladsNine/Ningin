#include "ShaderInfo.h"
#include "iostream"

ShaderInfo::ShaderInfo(string name, const filesystem::path& vertexPath, const filesystem::path& fragmentPath,
	const filesystem::path* geometryPath) : _name(name)
{
	AddPaths(vertexPath, fragmentPath, geometryPath);
}

void ShaderInfo::AddPaths(const filesystem::path& vertexPath, const filesystem::path& fragmentPath,
	const filesystem::path* geometryPath)
{
	_paths["vertex"] = vertexPath;
	_paths["fragment"] = fragmentPath;
	_geometryPath = geometryPath;
}

string ShaderInfo::GetName() 
{
	return _name;
}

const filesystem::path ShaderInfo::GetPath(const string& name) 
{
	return _paths.at(name);
}

const filesystem::path* ShaderInfo::GetOptionalShaderPath(const string& name)
{
	return _geometryPath;
}
