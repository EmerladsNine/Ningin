#include "sprite_info.h"

// Constructor
SpriteInfo::SpriteInfo(const std::string &name, const std::filesystem::path &path) : name(name), path(path), atlas_id(0)
{
}

// Getters
std::string SpriteInfo::getName() const
{
    return name;
}

std::filesystem::path SpriteInfo::getPath() const
{
    return path;
}

std::size_t SpriteInfo::getAtlasId() const
{
    return atlas_id;
}

// Setters
void SpriteInfo::setAtlasId(std::size_t atlasId)
{
    atlas_id = atlasId;
}
