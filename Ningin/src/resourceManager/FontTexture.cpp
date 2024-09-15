#include "FontTexture.h"
#include <stdexcept>

FontTexture::FontTexture() : _textureArray(0) {}

void FontTexture::GenerateTexture()
{
	glGenTextures(1, &_textureArray);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, _textureArray);

	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_R8, 256, 256, 128, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
}

void FontTexture::SetupCharTexture()
{
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void FontTexture::CreateCharTexture(FT_GlyphSlot glyph, unsigned char charCode)
{
	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, int(charCode), glyph->bitmap.width,
		glyph->bitmap.rows, 1, GL_RED, GL_UNSIGNED_BYTE, glyph->bitmap.buffer);
}

void FontTexture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

GLuint FontTexture::GetTextureArray()
{
	return _textureArray;
}
