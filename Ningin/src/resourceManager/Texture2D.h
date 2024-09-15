#pragma once

#include "../math/Dimensions2.h"
#include <stb_image.h>
#include "filesystem"
#include <GL/glew.h>
#include <string>
#include <vector>

using namespace std;

class Texture2D
{
	public:
		Texture2D(const filesystem::path& imgPath, bool alpha);
		~Texture2D();

		void Bind();

		GLuint GetID();
		Dimensions2 GetDimensions();

	private:
		vector<unsigned char> _data;
		filesystem::path _imgPath;

		Dimensions2 _dimensions;
		GLenum _imgFormat;
		GLuint _id;

		void SetupTexture(int width, int height);
		void CreateTextureMipmap();
		void LoadTexture();
};
