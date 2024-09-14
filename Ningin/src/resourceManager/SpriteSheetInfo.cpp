#include "SpriteSheetInfo.h"

SpriteSheetInfo::SpriteSheetInfo(vector<SpriteTile>& spriteTiles) : _spriteTiles(spriteTiles) {}

vector<SpriteTile> SpriteSheetInfo::GetSpriteTiles()
{
	return _spriteTiles;
}

void SpriteSheetInfo::SetSpriteTiles(vector<SpriteTile>& spriteTiles)
{
	_spriteTiles = spriteTiles;
}

void SpriteSheetInfo::AddSpriteTile(SpriteTile& spriteTile)
{
	_spriteTiles.push_back(spriteTile);
}
