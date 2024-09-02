#pragma once

#include <string>
#include <unordered_map>
#include <filesystem>

/**
    Struct representing shader information used to create a shader,
     including file paths and shader program name.

    Fields:
    - `paths`: An `unordered_map` mapping shader type identifiers ("vertex" and "fragment") to their respective file paths.
    - `name`: A `std::string` representing the name of the shader program.
*/

class ShaderInfo {
public:
    /**
        Creates a new `ShaderInfo` instance with specified shader paths and name.

        Returns: The newly created `ShaderInfo` instance.
    */
    ShaderInfo(const std::filesystem::path& vertex_path,
        const std::filesystem::path& fragment_path,
        const std::string& name);

    // Adds the paths for the vertex and fragment shaders to the `paths` unordered_map.
    void add_paths(const std::filesystem::path& vertex_path, const std::filesystem::path& fragment_path);
    std::string getName() const;
    std::filesystem::path getPath(std::string name) const;

private:
    std::unordered_map<std::string, std::filesystem::path> paths;
    std::string name;
};
