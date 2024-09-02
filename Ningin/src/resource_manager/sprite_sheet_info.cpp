#include "sprite_sheet_info.h"

// Constructor
SpriteSheetInfo::SpriteSheetInfo(const std::vector<SpriteTile>& spriteTiles)
    : sprite_tiles(spriteTiles) {}

// Getter
std::vector<SpriteTile> SpriteSheetInfo::getSpriteTiles() const {
    return sprite_tiles;
}

// Setter
void SpriteSheetInfo::setSpriteTiles(const std::vector<SpriteTile>& spriteTiles) {
    sprite_tiles = spriteTiles;
}

void SpriteSheetInfo::addSpriteTile(const SpriteTile& spriteTile)
{
    sprite_tiles.push_back(spriteTile);
}

std::vector<SpriteTile> SpriteSheetInfo::get_sprite_tiles()
{
    return this->sprite_tiles;
}
