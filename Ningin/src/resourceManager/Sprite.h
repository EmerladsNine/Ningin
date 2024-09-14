#pragma once

#include "../math/Dimensions2.h"

class Sprite
{
	public:
		Sprite(int spriteIndex, Dimensions2& dimensions);

		void SetDimensions(Dimensions2& dimensions);
		void SetSpriteIndex(int spriteIndex);

		Dimensions2& GetDimensions();
		int GetSpriteIndex();

	private:
		int _spriteIndex;
		Dimensions2 _dimensions;
};
