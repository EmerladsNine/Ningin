#pragma once

#include <GL/glew.h>
#include <filesystem>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <string>
#include <unordered_map>
#include <vector>

class Shader
{
  public:
    Shader(const std::filesystem::path &vertexPath, const std::filesystem::path &fragmentPath);
    ~Shader();

    void use() const;
    void setBool(std::string &name, bool value);
    void setInt(std::string &name, int value);
    void setIntWithLength(std::string &name, int length, std::vector<int> &values);
    void setFloat(std::string &name, float value);
    void setFloatVec4(std::string &name, float value1, float value2, float value3, float value4);
    void setMatrix4(std::string &name, glm::mat4 &matrix);
    void setMatrix4WithLength(std::string &name, int length, std::vector<glm::mat4> &matrices);

  private:
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;
    std::unordered_map<std::string, std::string> code;
    std::unordered_map<std::string, std::filesystem::path> paths;

    void loadShaders();
    void compileShaders();
    void createShaderProgram();
    void deleteShaders();
    void checkExtension(const std::filesystem::path &path, const std::string &expectedExtension) const;
    std::string loadShader(const std::filesystem::path &path) const;
    GLuint compileShader(GLenum shaderType, const std::string &source) const;
};
