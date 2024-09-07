#pragma once

#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H

class FontTexture {
public:
	FontTexture();
	~FontTexture();

	void generateTexture();
	void setupCharTexture();
	void createCharTexture(FT_GlyphSlot glyph, unsigned char charCode);
	void unbind() const;
	GLuint getTextureArray();

private:
	GLuint textureArray;
};
