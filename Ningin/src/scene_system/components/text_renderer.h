#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <glm.hpp>
#include <GL/glew.h>
#include <functional>
#include "../../resource_manager/resource_manager.h"
#include "../../resource_manager/color.h"
#include "../../resource_manager/shader.h"
#include "../../resource_manager/font.h"
#include "transform.h"
#include "../../math/dimensions2.h"
#include "../../ningin.h"
#include "../../math/math.h"

class Text {
public:
    Text(const std::string& fontName, const std::string& shaderName, const Color& textColor, const std::string& text, uint8_t fontSize);
    ~Text();

    void setTextColor(const Color& newColor);
    void setText(const std::string& text);
    void setFontSize(uint8_t fontSize);
    void setUserUniforms(std::function<void()> initFunc, std::function<void()> initDrawingFunc, std::function<void()> drawingFunc);
    void draw(const Transform& transform);

    //static void system(EntityManager& entityManager);

private:
    bool isStarted;
    Shader shader;
    Font font;
    Color textColor;
    std::string text;
    uint8_t fontSize;
    std::vector<glm::mat4> transforms;
    std::vector<int32_t> charsMap;
    Dimensions2 textDimensions;
    float letterDimensions;
    glm::mat4 baseModel;
    bool mustCalculate;
    bool userShader;
    std::unordered_map<std::string, std::function<void()>> userUniforms;
    GLuint vao;
    GLuint vbo;

    void initializeRenderData();
    void setShaderInitialUniforms();
    void initializeShaderInfo();
    void initializeVao();
    void initializeVbo();
    void setupVertexAttrib();
    void freeResources(bool unbindTexture);
    void configureDrawingContext();
    void renderText(int32_t length);
    std::pair<std::vector<std::vector<char>>, size_t> getTextInfo();
    void setInitDrawingUniforms();
    void setDrawingUniforms(int32_t length);
    void computeTextTransform(const Transform& transform);
    glm::mat4 computeLetterTransform(float xOffset, float xpos, float ypos, float scale);
    void calculateTextDimensions();
};
