#include "buffer.h"

Buffer::Buffer(GLint bufferType, unsigned long long uniformSize, float* vertexData, int flag) : _buffer(0)
{
	_bufferType = bufferType;
	GenBuffer(bufferType, uniformSize, vertexData, flag);
}

Buffer::Buffer() : _buffer(0) {}

GLuint Buffer::GetId()
{
	return _buffer;
}

void Buffer::GenBuffer(GLint bufferType, unsigned long long uniformSize, float* vertexData, GLint flag)
{
	glGenBuffers(1, &_buffer);
	glBindBuffer(bufferType, _buffer);
	glBufferData(bufferType, uniformSize, vertexData, flag);
}

void Buffer::BindBuffer()
{
	glBindBuffer(_bufferType, _buffer);
}
