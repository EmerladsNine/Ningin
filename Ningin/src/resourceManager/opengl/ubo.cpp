#include "ubo.h"
#include "GL/glew.h"
#include "buffer.h"

namespace Ningin
{
    UBO::UBO(vector<Shader> shadersUniforms, const string uboName, unsigned long long uniformSize) : _ubo(0)
    {
        for (auto& shader : shadersUniforms)
        {
            GLuint id = shader.GetID();
            glUniformBlockBinding(id, glGetUniformBlockIndex(id, uboName.c_str()), 0);
        }

        GenUBO(uniformSize);
    }

    UBO::UBO() : _ubo(0) {}

    void UBO::GenUBO(unsigned long long uniformSize)
    {

        Buffer ubo(GL_UNIFORM_BUFFER, uniformSize, NULL, GL_STATIC_DRAW);
        _ubo = ubo.GetId();

        glBindBufferRange(GL_UNIFORM_BUFFER, 0, _ubo, 0, uniformSize);
    }

    void UBO::SetUBOFloatPtr(unsigned long long uniformSize, unsigned long long offset, float* ptr)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, _ubo);
        glBufferSubData(GL_UNIFORM_BUFFER, offset, uniformSize, ptr);
    }

    void UBO::SetUBOIntPtr(unsigned long long uniformSize, unsigned long long offset, int* ptr)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, _ubo);
        glBufferSubData(GL_UNIFORM_BUFFER, offset, uniformSize, ptr);
    }

    GLuint UBO::getId()
    {
        return _ubo;
    }
}