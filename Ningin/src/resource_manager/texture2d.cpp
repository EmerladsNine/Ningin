#include "texture2d.h"
#include <iostream>
#include <stdexcept>

Texture2D::Texture2D(const std::filesystem::path &imgPath, bool alpha)
    : id(0), imgPath(imgPath), imgFormat(alpha ? GL_RGBA : GL_RGB)
{
    loadTexture();
    setupTexture(dimensions.width, dimensions.height);
    createTextureMipmap();
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &id);
}

void Texture2D::bind() const
{
    glBindTexture(GL_TEXTURE_2D, id);
}

GLuint Texture2D::getID()
{
    return id;
}

Dimensions2 Texture2D::getDimensions()
{
    return dimensions;
}

void Texture2D::setupTexture(int width, int height)
{
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexImage2D(GL_TEXTURE_2D, 0, imgFormat, width, height, 0, imgFormat, GL_UNSIGNED_BYTE,
                 data.empty() ? nullptr : data.data());

    // Set texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture2D::createTextureMipmap()
{
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture2D::loadTexture()
{
    int width, height, channels;
    unsigned char *imgData = stbi_load(imgPath.string().c_str(), &width, &height, &channels, 4);

    if (!imgData)
    {
        throw std::runtime_error("Failed to load image");
    }

    dimensions = Dimensions2(width, height);
    data.assign(imgData, imgData + width * height * 4);
    stbi_image_free(imgData);
}
