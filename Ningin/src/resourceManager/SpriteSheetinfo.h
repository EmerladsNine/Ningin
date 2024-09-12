#pragma once

#include "SpriteTile.h"
#include <vector>

class SpriteSheetInfo
{
	public:
		SpriteSheetInfo(std::vector<SpriteTile>& spriteTiles);

		void SetSpriteTiles(std::vector<SpriteTile>& spriteTiles);

		std::vector<SpriteTile> GetSpriteTiles();

		void AddSpriteTile(SpriteTile& spriteTile);

		std::vector<SpriteTile> GetSpriteTiles();

	private:
		std::vector<SpriteTile> spriteTiles;
};
