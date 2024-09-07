#include "font.h"
#include <iostream>
#include <stdexcept>

Font::Font(const std::filesystem::path& path, FT_Library ftLibrary)
	: fontPath(path), fontTexture() {
	prepareFont(ftLibrary);
}

FontTexture Font::getFontTexture()
{
	return fontTexture;
}

std::unordered_map<unsigned char, Character> Font::getCharMap()
{
	return charMap;
}

void Font::prepareFont(FT_Library ftLibrary) {
	FT_Face face = loadFont(ftLibrary);
	if (face != nullptr) {
		setupGlyphLoading(face);
		fontTexture.generateTexture();
		loadGlyphs(face);
		freeResources(face);
	}
}

FT_Face Font::loadFont(FT_Library ftLibrary) {
	FT_Face face = nullptr;
	if (FT_New_Face(ftLibrary, fontPath.string().c_str(), 0, &face)) {
		std::cerr << "Freetype failed to load font " << fontPath << ".\nLoading default font" << std::endl;
		// Return a default face or handle the error accordingly
	}
	return face;
}

void Font::setupGlyphLoading(FT_Face face) {
	FT_Set_Pixel_Sizes(face, 256, 256);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
}

void Font::loadGlyphs(FT_Face face) {
	if (face == nullptr) return;

	for (unsigned char charCode = 0; charCode < 128; ++charCode) {
		if (FT_Load_Char(face, charCode, FT_LOAD_RENDER)) {
			std::cerr << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
			continue;
		}
		FT_GlyphSlot glyph = face->glyph;

		fontTexture.createCharTexture(glyph, charCode);
		fontTexture.setupCharTexture();

		addGlyph(glyph, charCode);
	}
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void Font::addGlyph(FT_GlyphSlot glyph, unsigned char charCode) {
	Character character{
		static_cast<int>(charCode),
		{ static_cast<int>(glyph->bitmap.width), static_cast<int>(glyph->bitmap.rows) },
		{ glyph->bitmap_left, glyph->bitmap_top },
		static_cast<unsigned int>(glyph->advance.x >> 6),
	};

	charMap[charCode] = character;
}

void Font::freeResources(FT_Face face) {
	if (face != nullptr) {
		FT_Done_Face(face);
	}
}