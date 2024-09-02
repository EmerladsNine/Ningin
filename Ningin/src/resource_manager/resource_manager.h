#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include <stdexcept>
#include "Shader.h"
#include "texture2d.h"
#include "font.h"
#include "sprite_info.h"
#include "shader_info.h"
#include "texture_info.h"
#include "font_info.h"
#include "atlas.h"

class ResourceManager {
public:
    ResourceManager() = default;

    void addSprite(const SpriteInfo& info);
    void loadSprites(const std::vector<SpriteInfo>& info);
    void loadSpriteSheet();

    void loadShader(const ShaderInfo& info);
    void loadShaders(const std::vector<ShaderInfo>& info);

    Shader getShader(const std::string& name) const;

    void loadTexture(const TextureInfo& info);
    void loadTextures(const std::vector<TextureInfo>& info);

    Texture2D getTexture(const std::string& name) const;

    void loadFont(const FontInfo& info);
    void loadFonts(const std::vector<FontInfo>& info);
    void loadFontsFromFolder(const std::filesystem::path& path, FT_Library ftLibrary);

    Font getFont(const std::string& name) const;

private:
    std::unordered_map<std::string, Shader> shaders;
    std::unordered_map<std::string, Texture2D> textures;
    std::unordered_map<std::string, SpriteInfo> sprites;
    std::unordered_map<std::string, Font> fonts;
    std::vector<Atlas> atlases;
};
