#pragma once

#include "FontTexture.h"
#include <unordered_map>
#include FT_FREETYPE_H
#include "character.h"
#include <filesystem>
#include <ft2build.h>
#include <GL/glew.h>

using namespace std;

namespace Ningin
{
	class Font
	{
	public:
		Font(const filesystem::path& path);

		FontTexture GetFontTexture();
		unordered_map<GLchar, Character> GetCharMap();

	private:
		filesystem::path _fontPath;
		unordered_map<GLchar, Character> _charMap;
		FontTexture _fontTexture;

		void PrepareFont();
		FT_Face LoadFont();

		void SetupGlyphLoading(FT_Face face);
		void LoadGlyphs(FT_Face face);
		void AddGlyph(FT_GlyphSlot glyph, GLchar charCode);

		void FreeResources(FT_Face face);
	};
}