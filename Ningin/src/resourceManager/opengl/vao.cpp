#include "vao.h"

VAO::VAO() : _vao(0)
{
	GenVAO();
}

GLuint VAO::GetId()
{
	return _vao;
}

void VAO::GenVAO()
{
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
}

void VAO::BindVAO()
{
	glBindVertexArray(_vao);
}
