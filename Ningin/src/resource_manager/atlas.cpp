#include "atlas.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "texture2D.h"

Atlas::Atlas(size_t id) : atlasID(0), index(0), id(id) {
    generateAtlas();
}

void Atlas::generateAtlas() {
    glGenTextures(1, &atlasID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, atlasID);
    glTexImage3D(
        GL_TEXTURE_2D_ARRAY,
        0,
        GL_RGBA,
        256,
        256,
        256,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        nullptr
    );
}

void Atlas::addSprite(const std::filesystem::path& path, const std::string& name) {
    auto img = loadTexture(path);
    Dimensions2 dimensions(img.size(), img.size());

    addSpriteFromData(img, dimensions, name);
}

void Atlas::addSpritesWithJson(const std::filesystem::path& spriteSheetPath, const std::filesystem::path& infoPath) {
    SpriteSheetInfo info = parseJson(infoPath);
    addSprites(spriteSheetPath, info);
}

void Atlas::addSprites(const std::filesystem::path& spriteSheetPath, const SpriteSheetInfo& info) {
    Texture2D texture(spriteSheetPath, true);

    GLuint fbo = generateFrameBuffer(texture.getID());

    for (const auto& sprite : info.getSpriteTiles()) {
        addSpriteFromData(getSpriteTileData(sprite), sprite.getDimensions(), sprite.getName());
    }

    deleteFrameBuffer(fbo);
}

void Atlas::addSpriteFromData(const std::vector<uint8_t>& data, const Dimensions2& dimensions, const std::string& name) {
    createSpriteTexture(dimensions, data);
    setupSpriteTexture();

    sprites[name] = Sprite{ index, dimensions };
    ++index;
}

GLuint Atlas::generateFrameBuffer(GLuint texture) const {
    GLuint fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0,
        GL_TEXTURE_2D,
        texture,
        0
    );
    return fbo;
}

std::vector<uint8_t> Atlas::getSpriteTileData(const SpriteTile& sprite) const {
    std::vector<uint8_t> pixels(sprite.getDimensions().width * sprite.getDimensions().height * 4);
    glReadPixels(
        sprite.getInSheetPosition().x,
        sprite.getInSheetPosition().y,
        sprite.getDimensions().width,
        sprite.getDimensions().height,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        pixels.data()
    );
    return pixels;
}

void Atlas::deleteFrameBuffer(GLuint fbo) const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDeleteFramebuffers(1, &fbo);
}

std::vector<uint8_t> Atlas::loadTexture(const std::filesystem::path& path) const {
    // Implement texture loading using an image library of your choice
    // Here, we use a placeholder implementation
    return std::vector<uint8_t>(); // Placeholder
}

void Atlas::setupSpriteTexture() const {
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Atlas::createSpriteTexture(const Dimensions2& dimensions, const std::vector<uint8_t>& data) {
    glTexSubImage3D(
        GL_TEXTURE_2D_ARRAY,
        0,
        0,
        0,
        index,
        dimensions.width,
        dimensions.height,
        1,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        data.data()
    );
}

bool Atlas::canAddSprite() const {
    return index < 256 - 1;
}

bool Atlas::canAddSpriteSheet(const SpriteSheetInfo& spriteSheet) const {
    return (index + spriteSheet.getSpriteTiles().size()) < 256 - 1;
}

void Atlas::unbind() {
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void Atlas::bind() {
    glBindTexture(GL_TEXTURE_2D_ARRAY, atlasID);
}

SpriteSheetInfo Atlas::parseJson(const std::filesystem::path& infoPath) const {
    std::ifstream jsonFile(infoPath);
    if (!jsonFile.is_open()) {
        throw std::runtime_error("Failed to open JSON file");
    }

    Json::Value root;
    jsonFile >> root;

    std::vector<SpriteTile> spriteTiles;

    SpriteSheetInfo info(spriteTiles);

    if (root.isMember("spriteTiles")) {
        const Json::Value& spriteTiles = root["spriteTiles"];
        for (const auto& tile : spriteTiles) {
            SpriteTile spriteTile(std::string(""), Vector2(), Dimensions2());

            // Populate SpriteTile fields
            spriteTile.setName(tile["name"].asString());
            spriteTile.setDimensions(Dimensions2(tile["dimensions"]["width"].asInt(), tile["dimensions"]["height"].asInt()));
            spriteTile.setInSheetPosition(Vector2(tile["inSheetPosition"]["x"].asInt(), tile["inSheetPosition"]["y"].asInt()));

            // Add to the SpriteSheetInfo
            info.addSpriteTile(spriteTile);
        }
    }

    return info;
}

