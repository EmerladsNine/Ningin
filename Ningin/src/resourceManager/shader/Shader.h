#pragma once

#include <gtc/type_ptr.hpp>
#include <unordered_map>
#include <filesystem>
#include <GL/glew.h>
#include <glm.hpp>
#include <string>
#include <vector>

using namespace std;

namespace Ningin
{
	class Shader
	{
	public:
		Shader(const filesystem::path vertexPath, const filesystem::path fragmentPath,
			const filesystem::path* geometryPath = nullptr);

		void Use();
		void SetBool(const string& name, bool value);
		void SetInt(const string& name, int value);
		void SetIntWithLength(const string& name, int length, vector<int>& values);
		void SetFloat(const string& name, float value);
		void SetFloatVec4(const string& name, float value1, float value2, float value3, float value4);
		void SetFloatVec2WithLength(const string& name, int length, vector<glm::vec2> values);
		void SetMatrix4(const string& name, glm::mat4& matrix);
		void SetMatrix4WithLength(const string& name, int length, vector<glm::mat4>& matrices);

		GLuint GetID();

	private:
		GLuint _vertexShader;
		GLuint _fragmentShader;
		GLuint _geometryShader;
		GLuint _shaderProgram;

		unordered_map<string, filesystem::path> _paths;
		unordered_map<string, GLint> _uniformLocationCache;
		unordered_map<string, string> _code;

		bool _hasGeometry;

		void LoadShaders();
		void DeleteShaders();
		void CompileShaders();
		void CreateShaderProgram();
		void CheckExtension(filesystem::path& path, const string& expectedExtension);
		void CheckExtensions();

		GLint GetUniformLocation(const string& name);

		string LoadShader(filesystem::path& path);
		GLuint CompileShader(GLenum shaderType, string& source);
	};
}