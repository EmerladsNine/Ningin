#include "font.h"
#include <iostream>
#include <stdexcept>
#include "../ningin.h"

Font::Font(const filesystem::path& path) : _fontPath(path), _fontTexture()
{
	PrepareFont();
}

FontTexture Font::GetFontTexture()
{
	return _fontTexture;
}

unordered_map<GLchar, Character> Font::GetCharMap()
{
	return _charMap;
}

void Font::PrepareFont()
{
	FT_Face face = LoadFont();

	if (face != nullptr)
	{
		SetupGlyphLoading(face);
		_fontTexture.GenerateTexture();
		LoadGlyphs(face);
		FreeResources(face);
	}
}

FT_Face Font::LoadFont()
{
	FT_Face face = nullptr;
	if (FT_New_Face(ftLibrary, _fontPath.string().c_str(), 0, &face))
	{
		cerr << "Freetype failed to load font " << _fontPath << ".\nLoading default font" << endl;
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

	for (unsigned char charCode = 0; charCode < 128; ++charCode)
	{
		if (FT_Load_Char(face, charCode, FT_LOAD_RENDER))
		{
			cerr << "ERROR::FREETYPE: Failed to load Glyph" << endl;
			continue;
		}

		FT_GlyphSlot glyph = face->glyph;

		_fontTexture.CreateCharTexture(glyph, charCode);
		_fontTexture.SetupCharTexture();

		AddGlyph(glyph, charCode);
	}

	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void Font::AddGlyph(FT_GlyphSlot glyph, GLchar charCode)
{
	Character character {
		static_cast<int>(charCode),

		Dimensions2(static_cast<unsigned int>(glyph->bitmap.width),
			static_cast<unsigned int>(glyph->bitmap.rows)),

		Dimensions2(static_cast<unsigned int>(glyph->bitmap_left),
			static_cast<unsigned int>(glyph->bitmap_top)),

		static_cast<unsigned int>(glyph->advance.x)
	};
	_charMap.insert(make_pair(charCode, character));
}

void Font::FreeResources(FT_Face face)
{
	if (face != nullptr)
	{
		FT_Done_Face(face);
	}
}
