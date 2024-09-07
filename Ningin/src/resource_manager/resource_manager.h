#pragma once

#include "atlas.h"
#include "font.h"
#include "font_info.h"
#include "shader.h"
#include "shader_info.h"
#include "sprite_info.h"
#include "texture2d.h"
#include "texture_info.h"
#include <filesystem>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

class ResourceManager
{
  public:
    ResourceManager() = default;

    void addSprite(SpriteInfo &info);
    void loadSprites(std::vector<SpriteInfo> &info);
    void loadSpriteSheet();

    void loadShader(ShaderInfo &info);
    void loadShaders(std::vector<ShaderInfo> &info);

    Shader getShader(std::string &name);

    void loadTexture(TextureInfo &info);
    void loadTextures(std::vector<TextureInfo> &info);

    Texture2D getTexture(std::string &name);

    void loadFont(FontInfo &info);
    void loadFonts(std::vector<FontInfo> &info);
    void loadFontsFromFolder(std::filesystem::path &path, FT_Library ftLibrary);

    Font getFont(std::string &name);

  private:
    std::unordered_map<std::string, Shader> shaders;
    std::unordered_map<std::string, Texture2D> textures;
    std::unordered_map<std::string, SpriteInfo> sprites;
    std::unordered_map<std::string, Font> fonts;
    std::vector<Atlas> atlases;
};
