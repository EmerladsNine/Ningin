#include "Shader.h"
#include <format>
#include <fstream>
#include <sstream>

Shader::Shader(filesystem::path vertexPath, filesystem::path fragmentPath)
{
	_paths["vertex"] = vertexPath;
	_paths["fragment"] = fragmentPath;

	LoadShaders();
	CompileShaders();
	CreateShaderProgram();
	DeleteShaders();
}

void Shader::Use()
{
	glUseProgram(this->_shaderProgram);
}

void Shader::SetBool(const string& name, bool value)
{
	GLint location = GetUniformLocation(name);

	if (location != -1)
		glUniform1i(location, static_cast<int>(value));
}

void Shader::SetInt(const string& name, int value)
{
	GLint location = GetUniformLocation(name);

	if (location != -1)
		glUniform1i(location, value);
}

void Shader::SetIntWithLength(const string& name, int length, vector<int>& values)
{
	GLint location = GetUniformLocation(name);

	if (location != -1)
		glUniform1iv(location, length, values.data());
}

void Shader::SetFloat(const string& name, float value)
{
	GLint location = GetUniformLocation(name);

	if (location != -1)
		glUniform1f(location, value);
}

void Shader::SetFloatVec4(const string& name, float value1, float value2, float value3, float value4)
{
	GLint location = GetUniformLocation(name);

	if (location != -1)
		glUniform4f(location, value1, value2, value3, value4);
}

void Shader::SetFloatVec2WithLength(const string& name, int length, vector<glm::vec2> values)
{
	GLint location = GetUniformLocation(name);

	if (location != -1)
		glUniform2fv(location, length, glm::value_ptr(values[0]));
}

void Shader::SetMatrix4(const string& name, glm::mat4& matrix)
{
	GLint location = GetUniformLocation(name);

	if (location != -1)
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetMatrix4WithLength(const string& name, int length, vector<glm::mat4>& matrices)
{
	GLint location = GetUniformLocation(name);

	if (location != -1)
		glUniformMatrix4fv(location, length, GL_FALSE, glm::value_ptr(matrices[0]));
}

GLuint Shader::GetID()
{
	return _shaderProgram;
}

void Shader::LoadShaders()
{
	_code["vertex"] = LoadShader(_paths["vertex"]);
	_code["fragment"] = LoadShader(_paths["fragment"]);
}

void Shader::CompileShaders()
{
	_vertexShader = CompileShader(GL_VERTEX_SHADER, _code["vertex"]);
	_fragmentShader = CompileShader(GL_FRAGMENT_SHADER, _code["fragment"]);
}

void Shader::CreateShaderProgram()
{
	this->_shaderProgram = glCreateProgram();
	glAttachShader(_shaderProgram, _vertexShader);
	glAttachShader(_shaderProgram, _fragmentShader);
	glLinkProgram(_shaderProgram);

	GLint success = 0;
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLint logLength;
		glGetShaderiv(_shaderProgram, GL_INFO_LOG_LENGTH, &logLength);
		vector<char> infoLog(logLength);
		glGetProgramInfoLog(_shaderProgram, logLength, nullptr, infoLog.data());
		throw runtime_error(format("ERROR::SHADER::PROGRAM::LINKING_FAILED\n{}\n", infoLog.data()));
	}
}

void Shader::DeleteShaders()
{
	//glDetachShader(_shaderProgram, _vertexShader);
	//glDeleteShader(_vertexShader);
	//glDetachShader(_shaderProgram, _fragmentShader);
	//glDeleteShader(_fragmentShader);
}

void Shader::CheckExtension(filesystem::path& path, string& expectedExtension)
{
	if (path.extension() != expectedExtension)
	{
		throw runtime_error(format("Invalid shader(path: {}) file extension.]\nExpected a file extension of: {}\n", path.string(), expectedExtension));
	}
}

GLint Shader::GetUniformLocation(const string& name)
{
	if (_uniformLocationCache.find(name) != _uniformLocationCache.end())
		return _uniformLocationCache[name];

	GLint location = glGetUniformLocation(_shaderProgram, name.c_str());
	_uniformLocationCache[name] = location;

	return location;
}

string Shader::LoadShader(filesystem::path& path)
{
	ifstream file(path);
	if (!file)
	{
		throw runtime_error(format("Shader file of path: {} not found", path.string()));
	}

	file.open(path);

	stringstream buffer;
	buffer << file.rdbuf();

	file.close();

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
	if (!success)
	{
		GLint logLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
		vector<char> infoLog(logLength);
		glGetShaderInfoLog(shader, logLength, nullptr, infoLog.data());
		throw runtime_error(format("ERROR::SHADER::{}::COMPILATION_FAILED\n{}\n",
			(shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT"), infoLog.data()));
	}

	return shader;
}
