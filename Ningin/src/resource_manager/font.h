#pragma once

#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <unordered_map>
#include "font_texture.h"
#include "Character.h"
#include <filesystem>

class Font {
public:
    Font(const std::filesystem::path& path, FT_Library ftLibrary);
    FontTexture getFontTexture();
    std::unordered_map<unsigned char, Character> getCharMap();

private:
    std::filesystem::path fontPath;
    std::unordered_map<unsigned char, Character> charMap;
    FontTexture fontTexture;

    void prepareFont(FT_Library ftLibrary);
    FT_Face loadFont(FT_Library ftLibrary);
    void setupGlyphLoading(FT_Face face);
    void loadGlyphs(FT_Face face);
    void addGlyph(FT_GlyphSlot glyph, unsigned char charCode);
    void freeResources(FT_Face face);
};
