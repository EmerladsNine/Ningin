#include "SpriteInfo.h"

// ructor
SpriteInfo::SpriteInfo(std::string& name, std::filesystem::path& path) : name(name),
	path(path), atlasId(0) {}

std::string SpriteInfo::GetName()
{
	return name;
}

std::filesystem::path SpriteInfo::GetPath()
{
	return path;
}

std::size_t SpriteInfo::GetAtlasId()
{
	return atlasId;
}

void SpriteInfo::SetAtlasId(std::size_t atlasId)
{
	atlasId = atlasId;
}
