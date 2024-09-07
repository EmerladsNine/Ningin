#include "sprite_tile.h"

// Constructor
SpriteTile::SpriteTile(const std::string &name, const Vector2 &inSheetPosition, const Dimensions2 &dimensions)
    : name(name), in_sheet_position(inSheetPosition), dimensions(dimensions)
{
}

// Getters
std::string SpriteTile::getName() const
{
    return name;
}

Vector2 SpriteTile::getInSheetPosition() const
{
    return in_sheet_position;
}

Dimensions2 SpriteTile::getDimensions() const
{
    return dimensions;
}

// Setters
void SpriteTile::setName(const std::string &name)
{
    this->name = name;
}

void SpriteTile::setInSheetPosition(const Vector2 &inSheetPosition)
{
    in_sheet_position = inSheetPosition;
}

Vector2 SpriteTile::getInSheetPosition(const Vector2 &inSheetPosition)
{
    return inSheetPosition;
}

void SpriteTile::setDimensions(const Dimensions2 &dimensions)
{
    this->dimensions = dimensions;
}

Dimensions2 SpriteTile::getDimensions(const Dimensions2 &dimensions)
{
    return dimensions;
}
