#pragma once

#include "GL/glew.h"

class Buffer {
	public:
		Buffer(GLint bufferType, unsigned long long uniformSize, float* vertexData, int flag);
		Buffer();

		GLuint GetId();

	private:
		void GenBuffer(GLint bufferType, unsigned long long uniformSize, float* vertexData, GLint flag);

		void BindBuffer();

		GLuint _buffer;
		GLint _bufferType;
};
