#include "Character.h"

Character::Character(int asciiIndex, Dimensions2 size, Dimensions2 bearing, unsigned int advance)
	: asciiIndex(asciiIndex), size(size), bearing(bearing), advance(advance) {}

Character::Character() : asciiIndex(0), size(Dimensions2()), bearing(Dimensions2()), advance(0) {}
