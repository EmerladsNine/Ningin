#include "SpriteInfo.h"

SpriteInfo::SpriteInfo(string& name, filesystem::path& path) : _name(name),
	_path(path), _atlasId(0) {}

string SpriteInfo::GetName()
{
	return _name;
}

filesystem::path SpriteInfo::GetPath()
{
	return _path;
}

size_t SpriteInfo::GetAtlasId()
{
	return _atlasId;
}

void SpriteInfo::SetAtlasId(size_t atlasId)
{
	_atlasId = atlasId;
}
