#pragma once

#include "../math/dimensions2.h"

class Sprite {
public:
	// Constructor
	Sprite(int spriteIndex, const Dimensions2& dimensions);

	// Getters
	int getSpriteIndex() const;
	const Dimensions2& getDimensions() const;

	// Setters
	void setSpriteIndex(int spriteIndex);
	void setDimensions(const Dimensions2& dimensions);

private:
	int sprite_index;
	Dimensions2 dimensions;
};
