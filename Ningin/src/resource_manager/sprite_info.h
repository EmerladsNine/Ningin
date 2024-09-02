#pragma once

#include <string>
#include <filesystem>

class SpriteInfo {
public:
    // Constructor
    SpriteInfo(const std::string& name, const std::filesystem::path& path);

    // Getters
    std::string getName() const;
    std::filesystem::path getPath() const;
    std::size_t getAtlasId() const;

    // Setters
    void setAtlasId(std::size_t atlasId);

private:
    std::string name;
    std::filesystem::path path;
    std::size_t atlas_id;
};