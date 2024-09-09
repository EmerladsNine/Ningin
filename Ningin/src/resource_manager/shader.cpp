#include "shader.h"
#include <format>
#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
{
	paths["vertex"] = vertexPath;
	paths["fragment"] = fragmentPath;
	loadShaders();
	compileShaders();
	createShaderProgram();
	deleteShaders();
}

Shader::~Shader()
{
	glDeleteProgram(shaderProgram);
}

void Shader::use() const
{
	glUseProgram(shaderProgram);
}

void Shader::setBool(std::string& name, bool value)
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shader::setIntWithLength(std::string& name, int length, std::vector<int>& values)
{
	glUniform1iv(glGetUniformLocation(shaderProgram, name.c_str()), length, values.data());
}

void Shader::setFloat(std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shader::setFloatVec4(std::string& name, float value1, float value2, float value3, float value4)
{
	glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), value1, value2, value3, value4);
}

void Shader::setMatrix4(std::string& name, glm::mat4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setMatrix4WithLength(std::string& name, int length, std::vector<glm::mat4>& matrices)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), length, GL_FALSE,
		glm::value_ptr(matrices[0]));
}

void Shader::loadShaders()
{
	code["vertex"] = loadShader(paths["vertex"]);
	code["fragment"] = loadShader(paths["fragment"]);
}

void Shader::compileShaders()
{
	vertexShader = compileShader(GL_VERTEX_SHADER, code["vertex"]);
	fragmentShader = compileShader(GL_FRAGMENT_SHADER, code["fragment"]);
}

void Shader::createShaderProgram()
{
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	GLint success;
	// GLchar infoLog[1024];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLint logLength;
		glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> infoLog(logLength);
		glGetProgramInfoLog(shaderProgram, logLength, nullptr, infoLog.data());
		throw std::runtime_error(std::format("ERROR::SHADER::PROGRAM::LINKING_FAILED\n{}\n", infoLog.data()));
	}
}

void Shader::deleteShaders()
{
	glDetachShader(shaderProgram, vertexShader);
	glDeleteShader(vertexShader);
	glDetachShader(shaderProgram, fragmentShader);
	glDeleteShader(fragmentShader);
}

void Shader::checkExtension(const std::filesystem::path& path, const std::string& expectedExtension) const
{
	if (path.extension() != expectedExtension)
	{
		std::cerr << "Shader file " << path << " should have the '" << expectedExtension << "' extension" << std::endl;
		throw std::runtime_error("Invalid shader file extension");
	}
}

std::string Shader::loadShader(const std::filesystem::path& path) const
{
	std::ifstream file(path);
	if (!file.is_open())
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_FOUND: " << path << std::endl;
		throw std::runtime_error("Shader file not found");
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

GLuint Shader::compileShader(GLenum shaderType, const std::string& source) const
{
	GLuint shader = glCreateShader(shaderType);
	const char* sourceCStr = source.c_str();
	glShaderSource(shader, 1, &sourceCStr, nullptr);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLint logLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> infoLog(logLength);
		glGetShaderInfoLog(shader, logLength, nullptr, infoLog.data());
		throw std::runtime_error(std::format("ERROR::SHADER::{}::COMPILATION_FAILED\n{}\n",
			(shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT"), infoLog.data()));
	}

	return shader;
}