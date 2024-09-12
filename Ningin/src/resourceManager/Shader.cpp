#include "Shader.h"
#include <format>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

Shader::Shader(filesystem::path vertexPath, filesystem::path fragmentPath)
{
	paths["vertex"] = vertexPath;
	paths["fragment"] = fragmentPath;
	LoadShaders();
	CompileShaders();
	CreateShaderProgram();
	DeleteShaders();
}

Shader::~Shader()
{
	glDeleteProgram(shaderProgram);
}

void Shader::Use()
{
	glUseProgram(shaderProgram);
}

void Shader::SetBool(string& name, bool value)
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), static_cast<int>(value));
}

void Shader::SetInt(string& name, int value)
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shader::SetIntWithLength(string& name, int length, vector<int>& values)
{
	glUniform1iv(glGetUniformLocation(shaderProgram, name.c_str()), length, values.data());
}

void Shader::SetFloat(string& name, float value)
{
	glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shader::SetFloatVec4(string& name, float value1, float value2, float value3, float value4)
{
	glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), value1, value2, value3, value4);
}

void Shader::SetMatrix4(string& name, glm::mat4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetMatrix4WithLength(string& name, int length, vector<glm::mat4>& matrices)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), length, GL_FALSE,
		glm::value_ptr(matrices[0]));
}

void Shader::LoadShaders()
{
	code["vertex"] = LoadShader(paths["vertex"]);
	code["fragment"] = LoadShader(paths["fragment"]);
}

void Shader::CompileShaders()
{
	vertexShader = CompileShader(GL_VERTEX_SHADER, code["vertex"]);
	fragmentShader = CompileShader(GL_FRAGMENT_SHADER, code["fragment"]);
}

void Shader::CreateShaderProgram()
{
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	GLint success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		GLint logLength;
		glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);
		vector<char> infoLog(logLength);
		glGetProgramInfoLog(shaderProgram, logLength, nullptr, infoLog.data());
		throw runtime_error(format("ERROR::SHADER::PROGRAM::LINKING_FAILED\n{}\n", infoLog.data()));
	}
}

void Shader::DeleteShaders()
{
	glDetachShader(shaderProgram, vertexShader);
	glDeleteShader(vertexShader);
	glDetachShader(shaderProgram, fragmentShader);
	glDeleteShader(fragmentShader);
}

void Shader::CheckExtension(filesystem::path& path, string& expectedExtension)
{
	if (path.extension() != expectedExtension) {
		throw runtime_error(format("Invalid shader(path: {}) file extension.]\nExpected a file extension of: {}\n", path, expectedExtension));
	}
}

string Shader::LoadShader(filesystem::path& path)
{
	ifstream file(path);
	if (!file.is_open()) {
		throw runtime_error(format("Shader file of path: {} not found", path));
	}
	stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

GLuint Shader::CompileShader(GLenum shaderType, string& source)
{
	GLuint shader = glCreateShader(shaderType);
	const char* sourceCStr = source.c_str();
	glShaderSource(shader, 1, &sourceCStr, nullptr);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLint logLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
		vector<char> infoLog(logLength);
		glGetShaderInfoLog(shader, logLength, nullptr, infoLog.data());
		throw runtime_error(format("ERROR::SHADER::{}::CompILATION_FAILED\n{}\n",
			(shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT"), infoLog.data()));
	}

	return shader;
}
