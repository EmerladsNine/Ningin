#include "SpriteSheetInfo.h"

SpriteSheetInfo::SpriteSheetInfo(std::vector<SpriteTile>& spriteTiles) : spriteTiles(spriteTiles)
{
}

std::vector<SpriteTile> SpriteSheetInfo::GetSpriteTiles()
{
	return spriteTiles;
}

void SpriteSheetInfo::SetSpriteTiles(std::vector<SpriteTile>& spriteTiles)
{
	spriteTiles = spriteTiles;
}

void SpriteSheetInfo::AddSpriteTile(SpriteTile& spriteTile)
{
	spriteTiles.push_back(spriteTile);
}