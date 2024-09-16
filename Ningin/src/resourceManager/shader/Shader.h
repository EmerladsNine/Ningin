#pragma once

#include <gtc/type_ptr.hpp>
#include <unordered_map>
#include <filesystem>
#include <GL/glew.h>
#include <glm.hpp>
#include <string>
#include <vector>

using namespace std;

class Shader
{
	public:
		Shader(filesystem::path vertexPath, filesystem::path fragmentPath);

		void Use();
		void SetBool(string& name, bool value);
		void SetInt(string& name, int value);
		void SetIntWithLength(string& name, int length, vector<int>& values);
		void SetFloat(string& name, float value);
		void SetFloatVec4(string& name, float value1, float value2, float value3, float value4);
		void SetMatrix4(string& name, glm::mat4& matrix);
		void SetMatrix4WithLength(string& name, int length, vector<glm::mat4>& matrices);

		GLuint GetID();

	private:
		GLuint _vertexShader;
		GLuint _fragmentShader;
		GLuint _shaderProgram;

		unordered_map<string, filesystem::path> _paths;
		unordered_map<string, string> _code;

		void LoadShaders();
		void DeleteShaders();
		void CompileShaders();
		void CreateShaderProgram();
		void CheckExtension(filesystem::path& path, string& expectedExtension);

		string LoadShader(filesystem::path& path);
		GLuint CompileShader(GLenum shaderType, string& source);
};
