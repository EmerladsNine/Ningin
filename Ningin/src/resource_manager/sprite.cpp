#include "sprite.h"

// Constructor
Sprite::Sprite(int spriteIndex, const Dimensions2& dimensions)
	: sprite_index(spriteIndex), dimensions(dimensions) {}

// Getters
int Sprite::getSpriteIndex() const {
	return sprite_index;
}

const Dimensions2& Sprite::getDimensions() const {
	return dimensions;
}

// Setters
void Sprite::setSpriteIndex(int spriteIndex) {
	this->sprite_index = spriteIndex;
}

void Sprite::setDimensions(const Dimensions2& dimensions) {
	this->dimensions = dimensions;
}