#include "Sprite.h"

Sprite::Sprite(int spriteIndex, Dimensions2& dimensions) : spriteIndex(spriteIndex), dimensions(dimensions)
{
}

int Sprite::GetSpriteIndex()
{
	return spriteIndex;
}

Dimensions2& Sprite::GetDimensions()
{
	return dimensions;
}

void Sprite::SetSpriteIndex(int spriteIndex)
{
	this->spriteIndex = spriteIndex;
}

void Sprite::SetDimensions(Dimensions2& dimensions)
{
	this->dimensions = dimensions;
}
