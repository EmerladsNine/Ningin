#pragma once

#include <GL/glew.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <filesystem>
#include <stdexcept>
#include <memory>
#include <json/json.h>
#include "texture2D.h"
#include "sprite.h"
#include "sprite_tile.h"
#include "sprite_sheet_info.h"

class Atlas {
public:
    Atlas(size_t id);

    void generateAtlas();
    void addSprite(const std::filesystem::path& path, const std::string& name);
    void addSpritesWithJson(const std::filesystem::path& spriteSheetPath, const std::filesystem::path& infoPath);
    void addSprites(const std::filesystem::path& spriteSheetPath, const SpriteSheetInfo& info);
    bool canAddSprite() const;
    bool canAddSpriteSheet(const SpriteSheetInfo& spriteSheet) const;

    void unbind();
    void bind();

private:
    GLuint atlasID;
    std::unordered_map<std::string, Sprite> sprites;
    int index;
    size_t id;

    void addSpriteFromData(const std::vector<uint8_t>& data, const Dimensions2& dimensions, const std::string& name);
    GLuint generateFrameBuffer(GLuint texture) const;
    std::vector<uint8_t> getSpriteTileData(const SpriteTile& sprite) const;
    void deleteFrameBuffer(GLuint fbo) const;
    std::vector<uint8_t> loadTexture(const std::filesystem::path& path) const;
    void setupSpriteTexture() const;
    void createSpriteTexture(const Dimensions2& dimensions, const std::vector<uint8_t>& data);
    SpriteSheetInfo parseJson(const std::filesystem::path& infoPath) const;
};
