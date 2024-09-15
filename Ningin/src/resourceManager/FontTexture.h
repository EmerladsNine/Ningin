#pragma once

#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H

class FontTexture
{
	public:
		FontTexture();

		void GenerateTexture();
		void SetupCharTexture();

		void CreateCharTexture(FT_GlyphSlot glyph, unsigned char charCode);

		GLuint GetTextureArray();

		void Unbind();

	private:
		GLuint _textureArray;
};
