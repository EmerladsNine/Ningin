#pragma once

#include "../math/Dimensions2.h"

class Character
{
	public:
		Character(int asciiIndex, Dimensions2 size, Dimensions2 bearing, unsigned int advance);
		Character() = default;

		unsigned int advance;
		int asciiIndex;

		Dimensions2 bearing;
		Dimensions2 size;
};
