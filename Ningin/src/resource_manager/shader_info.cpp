#include "shader_info.h"

/**
    Creates a new `ShaderInfo` instance with specified shader paths and name.
*/
ShaderInfo::ShaderInfo(const std::filesystem::path &vertex_path, const std::filesystem::path &fragment_path,
                       const std::string &name)
    : name(name)
{
    add_paths(vertex_path, fragment_path);
}

/**
    Adds the paths for the vertex and fragment shaders to the `paths` unordered_map.
*/
void ShaderInfo::add_paths(const std::filesystem::path &vertex_path, const std::filesystem::path &fragment_path)
{
    paths["vertex"] = vertex_path;
    paths["fragment"] = fragment_path;
}

std::string ShaderInfo::getName() const
{
    return name;
}

std::filesystem::path ShaderInfo::getPath(std::string name) const
{
    return paths.at(name);
}
