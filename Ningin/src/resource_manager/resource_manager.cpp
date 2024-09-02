#include "resource_manager.h"
#include <fstream>
#include <json/json.h>

void ResourceManager::addSprite(const SpriteInfo& info) {
    if (atlases.empty() || !atlases.back().canAddSprite()) {
        atlases.emplace_back(atlases.size());
    }

    Atlas& atlas = atlases.back();
    atlas.addSprite(info.getPath(), info.getName());

    SpriteInfo spriteInfo = info;
    spriteInfo.setAtlasId(atlases.size() - 1);

    sprites[spriteInfo.getName()] = spriteInfo;
}

void ResourceManager::loadSprites(const std::vector<SpriteInfo>& info) {
    for (const auto& spriteInfo : info) {
        addSprite(spriteInfo);
    }
}

void ResourceManager::loadSpriteSheet() {
    // TODO: Implement loading sprite sheet functionality
}

void ResourceManager::loadShader(const ShaderInfo& info) {
    shaders[info.getName()] = Shader(info.getPath("vertex"), info.getPath("fragment"));
}

void ResourceManager::loadShaders(const std::vector<ShaderInfo>& info) {
    for (const auto& shaderInfo : info) {
        loadShader(shaderInfo);
    }
}

Shader ResourceManager::getShader(const std::string& name) const {
    auto it = shaders.find(name);
    if (it != shaders.end()) {
        return it->second;
    }
    throw std::runtime_error("Shader not found");
}

void ResourceManager::loadTexture(const TextureInfo& info) {
    textures[info.getName()] = Texture2D(info.getImgPath(), info.hasAlpha());
}

void ResourceManager::loadTextures(const std::vector<TextureInfo>& info) {
    for (const auto& textureInfo : info) {
        loadTexture(textureInfo);
    }
}

Texture2D ResourceManager::getTexture(const std::string& name) const {
    auto it = textures.find(name);
    if (it != textures.end()) {
        return it->second;
    }
    throw std::runtime_error("Texture not found");
}

void ResourceManager::loadFont(const FontInfo& info) {
    fonts[info.getName()] = Font(info.getFontPath(), info.getFtLibrary());
}

void ResourceManager::loadFonts(const std::vector<FontInfo>& info) {
    for (const auto& fontInfo : info) {
        loadFont(fontInfo);
    }
}

void ResourceManager::loadFontsFromFolder(const std::filesystem::path& path, FT_Library ftLibrary) {
    std::vector<FontInfo> fontInfos = FontInfo::generateInfoFromFolder(path, ftLibrary);
    for (const auto& fontInfo : fontInfos) {
        loadFont(fontInfo);
    }
}

Font ResourceManager::getFont(const std::string& name) const {
    auto it = fonts.find(name);
    if (it != fonts.end()) {
        return it->second;
    }
    throw std::runtime_error("Font not found");
}
