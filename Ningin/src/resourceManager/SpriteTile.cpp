#include "SpriteTile.h"

SpriteTile::SpriteTile(string name, Vector2 inSheetPosition, Dimensions2 dimensions)
	: name(name), inSheetPosition(inSheetPosition), dimensions(dimensions) {}

string SpriteTile::GetName()
{
	return name;
}

Vector2 SpriteTile::GetInSheetPosition()
{
	return inSheetPosition;
}

Dimensions2 SpriteTile::GetDimensions()
{
	return dimensions;
}

void SpriteTile::SetName(string& name)
{
	this->name = name;
}

void SpriteTile::SetInSheetPosition(Vector2& inSheetPosition)
{
	inSheetPosition = inSheetPosition;
}

void SpriteTile::SetDimensions(Dimensions2& dimensions)
{
	this->dimensions = dimensions;
}
