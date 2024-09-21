#pragma once

#include "GL/glew.h"

class VAO {
	public:
		VAO();

		void BindVAO();

		GLuint GetId();

	private:
		void GenVAO();

		GLuint _vao;
};
