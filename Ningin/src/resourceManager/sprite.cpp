#include "Sprite.h"

Sprite::Sprite(int spriteIndex, Dimensions2& dimensions) : _spriteIndex(spriteIndex),
	_dimensions(dimensions) {}

int Sprite::GetSpriteIndex()
{
	return _spriteIndex;
}

Dimensions2& Sprite::GetDimensions()
{
	return _dimensions;
}

void Sprite::SetSpriteIndex(int spriteIndex)
{
	_spriteIndex = spriteIndex;
}

void Sprite::SetDimensions(Dimensions2& dimensions)
{
	_dimensions = dimensions;
}
