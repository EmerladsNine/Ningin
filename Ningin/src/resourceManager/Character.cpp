#include "Character.h"

Character::Character(int asciiIndex, Dimensions2 size, Dimensions2 bearing, unsigned int advance)
	: _asciiIndex(asciiIndex), _size(size), _bearing(bearing), _advance(advance) {}

int Character::GetAsciiIndex()
{
	return _asciiIndex;
}

Dimensions2& Character::GetSize()
{
	return _size;
}

Dimensions2& Character::GetBearing()
{
	return _bearing;
}

unsigned int Character::GetAdvance()
{
	return _advance;
}
