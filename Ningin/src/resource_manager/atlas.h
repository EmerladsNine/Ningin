#pragma once

#include <GL/glew.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <filesystem>
#include <stdexcept>
#include <memory>
//#include <json/json.h>
#include "texture2D.h"
#include "sprite.h"
#include "sprite_tile.h"
#include "sprite_sheet_info.h"

class Atlas {
public:
    Atlas(size_t id);

    void generateAtlas();
    void addSprite( std::filesystem::path& path,  std::string& name);
    void addSpritesWithJson( std::filesystem::path& spriteSheetPath,  std::filesystem::path& infoPath);
    void addSprites( std::filesystem::path& spriteSheetPath,  SpriteSheetInfo& info);
    bool canAddSprite() ;
    bool canAddSpriteSheet( SpriteSheetInfo& spriteSheet) ;

    void unbind();
    void bind();

private:
    GLuint atlasID;
    std::unordered_map<std::string, Sprite> sprites;
    int index;
    size_t id;

    void addSpriteFromData( std::vector<uint8_t>& data,  Dimensions2& dimensions,  std::string& name);
    GLuint generateFrameBuffer(GLuint texture) ;
    std::vector<uint8_t> getSpriteTileData( SpriteTile& sprite) ;
    void deleteFrameBuffer(GLuint fbo) ;
    std::vector<unsigned char> loadTexture( std::filesystem::path& path) ;
    void setupSpriteTexture() ;
    void createSpriteTexture( Dimensions2& dimensions,  std::vector<uint8_t>& data);
    SpriteSheetInfo parseJson( std::filesystem::path& infoPath) ;
};
