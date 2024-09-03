#include "text_renderer.h"
#include <gtc/matrix_transform.hpp>

// ructor
Text::Text( std::string& fontName,  std::string& shaderName,  Color& textColor,  std::string& text, uint8_t fontSize)
    : isStarted(false),
    shader(resourceManager.getShader(shaderName)),
    font(resourceManager.getFont(fontName)),
    textColor(textColor),
    text(text),
    fontSize(fontSize),
    letterDimensions(48.0f),
    baseModel(glm::mat4(1.0f)),
    mustCalculate(true),
    userShader(shaderName != "text"),
    vao(0),
    vbo(0) {
    setShaderInitialUniforms();
    initializeRenderData();
}

Text::~Text() {
    glDeleteVertexArrays(1, &vao);
}

void Text::initializeRenderData() {
    calculateTextDimensions();
    initializeShaderInfo();
    initializeVao();
    initializeVbo();
    setupVertexAttrib();
    freeResources(false);
}

void Text::setShaderInitialUniforms() {
    std::string projectionMatrixName = std::string("projection");
    std::string TextSamplerName = std::string("text");

    shader.setInt(TextSamplerName, 0);
    shader.setMatrix4(projectionMatrixName, projectionMatrix);

    if (userUniforms.count("init")) {
        userUniforms["init"]();
    }
}

void Text::initializeShaderInfo() {
    for (int i = 0; i < ARRAY_LIMIT; i++) {
        transforms.push_back(glm::mat4(1.0f));
        charsMap.push_back(0);
    }
}

void Text::initializeVao() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

void Text::initializeVbo() {
     float vertexData[] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
    };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
}

void Text::setupVertexAttrib() {
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
}

void Text::freeResources(bool unbindTexture) {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    if (unbindTexture) {
        glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    }
}

void Text::configureDrawingContext() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, font.getFontTexture().getTextureArray());
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindVertexArray(vao);
}

void Text::draw(Transform& transform) {
    setInitDrawingUniforms();
    configureDrawingContext();

    if (mustCalculate) {
        computeTextTransform(transform);
    }

    Vector3 pos = transform.getPosition();
    float scale = static_cast<float>(fontSize) / 256.0f;
    float hBearing = font.getCharMap().at('H').getBearing().height;
    int32_t workingIndex = 0;
    float xOffset = 0.0f;

    for (char c : text) {
         auto& ch = font.getCharMap().at(c);

        if (c == '\n') {
            pos.y += ch.getSize().height * 1.3f * scale;
            xOffset = 0.0f;
        }
        else if (c == ' ') {
            xOffset += (ch.getAdvance() >> 6) * scale;
        }
        else {
            float xpos = ch.getBearing().width * scale;
            float ypos = pos.y + (hBearing - ch.getBearing().height) * scale;

            transforms[workingIndex] = computeLetterTransform(xOffset, xpos, ypos, letterDimensions);
            charsMap[workingIndex] = ch.getAsciiIndex();

            if (workingIndex == ARRAY_LIMIT - 1) {
                renderText(workingIndex);
                workingIndex = 0;
            }

            xOffset += (ch.getAdvance() >> 6) * scale;
            workingIndex++;
        }
    }

    renderText(workingIndex);
    freeResources(true);
}

void Text::renderText(int32_t length) {
    if (length != 0) {
        setDrawingUniforms(length);
        glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, length);
    }
}

void Text::calculateTextDimensions() {
    auto [splitedText, longestLine] = getTextInfo();
    textDimensions.height = static_cast<int32_t>(splitedText.size() * fontSize +
        font.getCharMap().at('\n').getSize().height * 1.3f * fontSize / 256.0f);
    textDimensions.width = static_cast<int32_t>(longestLine * fontSize);
}

std::pair<std::vector<std::vector<char>>, size_t> Text::getTextInfo() {
    std::vector<std::vector<char>> splitedText;
    splitedText.push_back(std::vector<char>());
    size_t currentLine = 0;
    size_t longestLine = 0;

    for (char c : text) {
        if (c == '\n') {
            if (longestLine < splitedText[currentLine].size()) {
                longestLine = splitedText[currentLine].size();
            }
            splitedText.push_back(std::vector<char>());
            currentLine++;
            continue;
        }
        splitedText[currentLine].push_back(c);
    }

    return { splitedText, longestLine };
}

void Text::setInitDrawingUniforms() {
    std::string projectionMatrixName = std::string("projection");
    std::string TextColorName = std::string("TextColor");

    shader.setMatrix4(projectionMatrixName, projectionMatrix);

    if (userUniforms.count("init_drawing")) {
        userUniforms["init_drawing"]();
        return;
    }

    shader.setFloatVec4(
        TextColorName,
        textColor.r / 255.0f,
        textColor.g / 255.0f,
        textColor.b / 255.0f,
        textColor.a / 255.0f
    );
}

void Text::setDrawingUniforms(int32_t length) {
    std::string transformsName = std::string("Transforms");
    std::string charsMapName = std::string("CharsMap");
    shader.setMatrix4WithLength(transformsName, length, transforms);
    shader.setIntWithLength(charsMapName, length, charsMap);

    if (userUniforms.count("drawing")) {
        userUniforms["drawing"]();
    }
}

glm::mat4 Text::computeLetterTransform(float xOffset, float xpos, float ypos, float scale) {
    glm::mat4 letterModel = baseModel;

    letterModel = glm::translate(letterModel, glm::vec3(xOffset + xpos, ypos, 0.0f));
    letterModel = glm::scale(letterModel, glm::vec3(scale, scale, 1.0f));

    return letterModel;
}

void Text::computeTextTransform(Transform& transform) {
    Vector3 pos = transform.getPosition();
    float scale = static_cast<float>(fontSize) / 256.0f;

    Vector2 text_center = {textDimensions.width * scale / 2.0f, textDimensions.height * scale / 2.0f };

    baseModel = glm::translate(baseModel, glm::vec3(pos.x, pos.y, 0.0f));
    baseModel = glm::translate(baseModel, glm::vec3(text_center.x, text_center.y, 0.0f));
    baseModel = glm::rotate(baseModel, transform.getRotation().z, glm::vec3(0.0f, 0.0f, 1.0f));
    baseModel = glm::translate(baseModel, glm::vec3(-text_center.x, -text_center.y, 0.0f));

    mustCalculate = false;
}

void Text::setUserUniforms(std::function<void()> initFunc, std::function<void()> initDrawingFunc, std::function<void()> drawingFunc) {
    userUniforms["init"] = initFunc;
    userUniforms["init_drawing"] = initDrawingFunc;
    userUniforms["drawing"] = drawingFunc;
}

void Text::setTextColor( Color& newColor) {
    textColor = newColor;
}

void Text::setText( std::string& text) {
    this->text = text;
    mustCalculate = true;
}

void Text::setFontSize(uint8_t fontSize) {
    this->fontSize = fontSize;
    mustCalculate = true;
}

//void Text::system(EntityManager& entityManager) {
//
//}
