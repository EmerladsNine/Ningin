#pragma once

#include "FontTexture.h"
#include <unordered_map>
#include FT_FREETYPE_H
#include "character.h"
#include <filesystem>
#include <ft2build.h>
#include <GL/glew.h>

class Font
{
	public:
		Font(std::filesystem::path& path, FT_Library ftLibrary);

		FontTexture GetFontTexture();
		std::unordered_map<unsigned char, Character> GetCharMap();

	private:
		std::filesystem::path fontPath;
		std::unordered_map<unsigned char, Character> charMap;
		FontTexture fontTexture;

		void PrepareFont(FT_Library ftLibrary);
		FT_Face LoadFont(FT_Library ftLibrary);

		void SetupGlyphLoading(FT_Face face);
		void LoadGlyphs(FT_Face face);
		void AddGlyph(FT_GlyphSlot glyph, unsigned char charCode);

		void FreeResources(FT_Face face);
};
