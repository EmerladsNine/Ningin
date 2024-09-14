#pragma once

#include "../math/Dimensions2.h"

class Character
{
	public:
		Character(int asciiIndex, Dimensions2 size, Dimensions2 bearing, unsigned int advance);
		Character() = default;

		unsigned int GetAdvance();
		int GetAsciiIndex();

		Dimensions2& GetBearing();
		Dimensions2& GetSize();

	private:
		unsigned int _advance;
		int _asciiIndex;

		Dimensions2 _bearing;
		Dimensions2 _size;
};
