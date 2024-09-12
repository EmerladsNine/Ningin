#include "Character.h"

Character::Character(int asciiIndex, Dimensions2 size, Dimensions2 bearing, unsigned int advance)
	: asciiIndex(asciiIndex), size(size), bearing(bearing), advance(advance) {}

int Character::GetAsciiIndex()
{
	return asciiIndex;
}

Dimensions2& Character::GetSize()
{
	return size;
}

Dimensions2& Character::GetBearing()
{
	return bearing;
}

unsigned int Character::GetAdvance()
{
	return advance;
}
