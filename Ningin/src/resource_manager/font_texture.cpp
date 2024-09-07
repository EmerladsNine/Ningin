#include "font_texture.h"
#include <stdexcept>

FontTexture::FontTexture() : textureArray(0) {}

FontTexture::~FontTexture() {
	if (textureArray != 0) {
		glDeleteTextures(1, &textureArray);
	}
}

void FontTexture::generateTexture() {
	glGenTextures(1, &textureArray);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);

	glTexImage3D(
		GL_TEXTURE_2D_ARRAY,
		0,
		GL_R8,
		256,
		256,
		128,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		nullptr
	);
}

void FontTexture::setupCharTexture() {
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void FontTexture::createCharTexture(FT_GlyphSlot glyph, unsigned char charCode) {
	glTexSubImage3D(
		GL_TEXTURE_2D_ARRAY,
		0,
		0,
		0,
		charCode,
		glyph->bitmap.width,
		glyph->bitmap.rows,
		1,
		GL_RED,
		GL_UNSIGNED_BYTE,
		glyph->bitmap.buffer
	);
}

void FontTexture::unbind() const {
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

GLuint FontTexture::getTextureArray()
{
	return textureArray;
}