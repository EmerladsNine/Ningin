#include "resource_manager.h"
#include <fstream>
#include <json/json.h>

void ResourceManager::addSprite( SpriteInfo& info) {
    if (atlases.empty() || !atlases.back().canAddSprite()) {
        atlases.emplace_back(atlases.size());
    }

    Atlas& atlas = atlases.back();
    std::filesystem::path path = info.getPath();
    std::string name = info.getName();
    atlas.addSprite(path, name);

    SpriteInfo spriteInfo = info;
    spriteInfo.setAtlasId(atlases.size() - 1);

    sprites[spriteInfo.getName()] = spriteInfo;
}

void ResourceManager::loadSprites( std::vector<SpriteInfo>& info) {
    for ( auto& spriteInfo : info) {
        addSprite(spriteInfo);
    }
}

void ResourceManager::loadSpriteSheet() {
    // TODO: Implement loading sprite sheet functionality
}

void ResourceManager::loadShader( ShaderInfo& info) {
    Shader shader(info.getPath("vertex"), info.getPath("fragment"));
    shaders.insert(std::make_pair(info.getName(), shader));
}

void ResourceManager::loadShaders( std::vector<ShaderInfo>& info) {
    for ( auto& shaderInfo : info) {
        loadShader(shaderInfo);
    }
}

Shader ResourceManager::getShader( std::string& name)  {
    auto it = shaders.find(name);
    if (it != shaders.end()) {
        return it->second;
    }
    throw std::runtime_error("Shader not found");
}

void ResourceManager::loadTexture(TextureInfo& info) {
    Texture2D texture(info.getImgPath(), info.hasAlpha());
    textures.insert(std::make_pair(info.getName(), texture));
}

void ResourceManager::loadTextures( std::vector<TextureInfo>& info) {
    for ( auto& textureInfo : info) {
        loadTexture(textureInfo);
    }
}

Texture2D ResourceManager::getTexture( std::string& name)  {
    auto it = textures.find(name);
    if (it != textures.end()) {
        return it->second;
    }
    throw std::runtime_error("Texture not found");
}

void ResourceManager::loadFont( FontInfo& info) {
    Font font(info.getFontPath(), info.getFtLibrary());
    fonts.insert(std::make_pair(info.getName(), font));
}

void ResourceManager::loadFonts( std::vector<FontInfo>& info) {
    for ( auto& fontInfo : info) {
        loadFont(fontInfo);
    }
}

void ResourceManager::loadFontsFromFolder( std::filesystem::path& path, FT_Library ftLibrary) {
    std::vector<FontInfo> fontInfos = FontInfo::generateInfoFromFolder(path, ftLibrary);
    for ( auto& fontInfo : fontInfos) {
        loadFont(fontInfo);
    }
}

Font ResourceManager::getFont( std::string& name)  {
    auto it = fonts.find(name);
    if (it != fonts.end()) {
        return it->second;
    }
    throw std::runtime_error("Font not found");
}
