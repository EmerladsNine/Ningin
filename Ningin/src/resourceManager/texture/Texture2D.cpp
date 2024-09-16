#include "Texture2D.h"
#include <iostream>
#include <stdexcept>

Texture2D::Texture2D(const filesystem::path& imgPath, bool alpha) : _id(0), _imgPath(imgPath),
	_imgFormat(alpha ? GL_RGBA : GL_RGB)
{
	LoadTexture();
	SetupTexture(_dimensions.width, _dimensions.height);
	CreateTextureMipmap();
}

void Texture2D::Bind() 
{
	glBindTexture(GL_TEXTURE_2D, _id);
}

GLuint Texture2D::GetID()
{
	return _id;
}

Dimensions2 Texture2D::GetDimensions()
{
	return _dimensions;
}

void Texture2D::SetupTexture(int width, int height)
{
	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);

	glTexImage2D(GL_TEXTURE_2D, 0, _imgFormat, width, height, 0, _imgFormat, GL_UNSIGNED_BYTE,
		_data.empty() ? nullptr : _data.data());

	// Set texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture2D::CreateTextureMipmap()
{
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture2D::LoadTexture()
{
	int width, height, channels;
	unsigned char* imgData = stbi_load(_imgPath.string().c_str(), &width, &height, &channels, 4);

	if (!imgData)
	{
		throw runtime_error("Failed to load image");
	}

	_dimensions = Dimensions2(width, height);
	_data.assign(imgData, imgData + width * height * 4);
	stbi_image_free(imgData);
}
