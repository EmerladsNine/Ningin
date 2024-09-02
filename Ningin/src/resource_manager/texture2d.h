#pragma once

#include <string>
#include <vector>
#include <GL/glew.h>
#include <stb_image.h>
#include "../math/dimensions2.h"
#include "filesystem"

class Texture2D {
public:
    Texture2D(const std::filesystem::path& imgPath, bool alpha);
    ~Texture2D();

    void bind() const;

    GLuint getID();
    Dimensions2 getDimensions();

private:
    GLuint id;
    std::filesystem::path imgPath;
    std::vector<unsigned char> data;
    GLenum imgFormat;
    Dimensions2 dimensions;

    void setupTexture(int width, int height);
    void createTextureMipmap();
    void loadTexture();
};
