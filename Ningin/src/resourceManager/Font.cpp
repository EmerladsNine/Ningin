#include "font.h"
#include <iostream>
#include <stdexcept>

using namespace std;

Font::Font(filesystem::path& path, FT_Library ftLibrary) : fontPath(path), fontTexture()
{
	PrepareFont(ftLibrary);
}

FontTexture Font::GetFontTexture()
{
	return fontTexture;
}

unordered_map<unsigned char, Character> Font::GetCharMap()
{
	return charMap;
}

void Font::PrepareFont(FT_Library ftLibrary)
{
	FT_Face face = LoadFont(ftLibrary);

	if (face != nullptr) {
		SetupGlyphLoading(face);
		fontTexture.GenerateTexture();
		LoadGlyphs(face);
		FreeResources(face);
	}
}

FT_Face Font::LoadFont(FT_Library ftLibrary)
{
	FT_Face face = nullptr;
	if (FT_New_Face(ftLibrary, fontPath.string().c_str(), 0, &face)) {
		cerr << "Freetype failed to load font " << fontPath << ".\nLoading default font" << endl;
		// Return a default face or handle the error accordingly
	}
	return face;
}

void Font::SetupGlyphLoading(FT_Face face)
{
	FT_Set_Pixel_Sizes(face, 256, 256);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
}

void Font::LoadGlyphs(FT_Face face)
{
	if (face == nullptr)
		return;

	for (unsigned char charCode = 0; charCode < 128; ++charCode) {
		if (FT_Load_Char(face, charCode, FT_LOAD_RENDER)) {
			cerr << "ERROR::FREETYPE: Failed to load Glyph" << endl;
			continue;
		}

		FT_GlyphSlot glyph = face->glyph;

		fontTexture.CreateCharTexture(glyph, charCode);
		fontTexture.SetupCharTexture();

		AddGlyph(glyph, charCode);
	}

	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void Font::AddGlyph(FT_GlyphSlot glyph, unsigned char charCode)
{
	Character character {
		static_cast<int>(charCode),
		Dimensions2(static_cast<unsigned int>(glyph->bitmap.width), static_cast<unsigned int>(glyph->bitmap.rows)),
		Dimensions2(static_cast<unsigned int>(glyph->bitmap_left), static_cast<unsigned int>(glyph->bitmap_top)),
		static_cast<unsigned int>(glyph->advance.x >> 6)
	};

	charMap[charCode] = character;
}

void Font::FreeResources(FT_Face face)
{
	if (face != nullptr) {
		FT_Done_Face(face);
	}
}
