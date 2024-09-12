#pragma once

#include "../math/Dimensions2.h"
#include <stb_image.h>
#include "filesystem"
#include <GL/glew.h>
#include <string>
#include <vector>

class Texture2D
{
	public:
		Texture2D(std::filesystem::path& imgPath, bool alpha);
		~Texture2D();

		void Bind();

		GLuint GetID();
		Dimensions2 GetDimensions();

	private:
		std::vector<unsigned char> data;
		std::filesystem::path imgPath;

		Dimensions2 dimensions;
		GLenum imgFormat;
		GLuint id;

		void SetupTexture(int width, int height);
		void CreateTextureMipmap();
		void LoadTexture();
};
