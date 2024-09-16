#include "SpriteTile.h"

SpriteTile::SpriteTile(string name, Vector2 inSheetPosition, Dimensions2 dimensions)
	: _name(name), _inSheetPosition(inSheetPosition), _dimensions(dimensions) {}

string SpriteTile::GetName()
{
	return _name;
}

Vector2 SpriteTile::GetInSheetPosition()
{
	return _inSheetPosition;
}

Dimensions2 SpriteTile::GetDimensions()
{
	return _dimensions;
}

void SpriteTile::SetName(string& name)
{
	this->_name = name;
}

void SpriteTile::SetInSheetPosition(Vector2& inSheetPosition)
{
	_inSheetPosition = inSheetPosition;
}

void SpriteTile::SetDimensions(Dimensions2& dimensions)
{
	this->_dimensions = dimensions;
}
