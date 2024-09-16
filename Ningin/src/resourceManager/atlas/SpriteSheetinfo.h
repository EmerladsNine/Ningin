#pragma once

#include "SpriteTile.h"
#include <vector>

using namespace std;

class SpriteSheetInfo
{
	public:
		SpriteSheetInfo(vector<SpriteTile>& spriteTiles);

		void SetSpriteTiles(vector<SpriteTile>& spriteTiles);

		vector<SpriteTile> GetSpriteTiles();

		void AddSpriteTile(SpriteTile& spriteTile);

	private:
		vector<SpriteTile> _spriteTiles;
};
