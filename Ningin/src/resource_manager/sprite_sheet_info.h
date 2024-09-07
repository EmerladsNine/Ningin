#pragma once

#include "sprite_tile.h"
#include <vector>

class SpriteSheetInfo
{
  public:
    // Constructor
    SpriteSheetInfo(const std::vector<SpriteTile> &spriteTiles);

    // Getters
    std::vector<SpriteTile> getSpriteTiles() const;

    // Setters
    void setSpriteTiles(const std::vector<SpriteTile> &spriteTiles);
    void addSpriteTile(const SpriteTile &spriteTile);

    std::vector<SpriteTile> get_sprite_tiles();

  private:
    std::vector<SpriteTile> sprite_tiles;
};
