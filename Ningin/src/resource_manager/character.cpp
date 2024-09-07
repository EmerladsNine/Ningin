#include "character.h"

// Constructor
Character::Character(int ascii_index, const Dimensions2& size, const Dimensions2& bearing, unsigned int advance)
	: ascii_index(ascii_index), size(size), bearing(bearing), advance(advance) {}

// Accessors
int Character::getAsciiIndex() const {
	return ascii_index;
}

const Dimensions2& Character::getSize() const {
	return size;
}

const Dimensions2& Character::getBearing() const {
	return bearing;
}

unsigned int Character::getAdvance() const {
	return advance;
}