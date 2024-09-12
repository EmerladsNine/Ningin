#pragma once

#include <gtc/type_ptr.hpp>
#include <unordered_map>
#include <filesystem>
#include <GL/glew.h>
#include <glm.hpp>
#include <string>
#include <vector>

class Shader
{
	public:
		Shader(std::filesystem::path vertexPath, std::filesystem::path fragmentPath);
		~Shader();

		void Use();
		void SetBool(std::string& name, bool value);
		void SetInt(std::string& name, int value);
		void SetIntWithLength(std::string& name, int length, std::vector<int>& values);
		void SetFloat(std::string& name, float value);
		void SetFloatVec4(std::string& name, float value1, float value2, float value3, float value4);
		void SetMatrix4(std::string& name, glm::mat4& matrix);
		void SetMatrix4WithLength(std::string& name, int length, std::vector<glm::mat4>& matrices);

	private:
		GLuint vertexShader;
		GLuint fragmentShader;
		GLuint shaderProgram;

		std::unordered_map<std::string, std::filesystem::path> paths;
		std::unordered_map<std::string, std::string> code;

		void LoadShaders();
		void DeleteShaders();
		void CompileShaders();
		void CreateShaderProgram();
		void CheckExtension(std::filesystem::path& path, std::string& expectedExtension);

		std::string LoadShader(std::filesystem::path& path);
		GLuint CompileShader(GLenum shaderType, std::string& source);
};
