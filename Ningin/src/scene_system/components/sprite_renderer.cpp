#include "sprite_renderer.h"

Sprite::Sprite(
     std::string& textureName,
     std::string& shaderName,
     Color& tintingColor,
    bool useTint,
    bool alpha)
    : isStarted(false),
    alpha(alpha),
    tintingColor(tintingColor),
    useTint(useTint),
    shader(resourceManager.getShader(shaderName)),
    texture(resourceManager.getTexture(textureName)),
    userShader(shaderName != "sprite"),
    quadVAO(0) {

    initializeRenderData();
    setShaderInitialUniforms();
}

Sprite::~Sprite() {
    glDeleteVertexArrays(1, &quadVAO);
}

void Sprite::initializeRenderData() {
    initializeVAO();
    initializeVBO();
    setupVertexAttrib();
    freeInitializationResources();
}

void Sprite::initializeVAO() {
    glGenVertexArrays(1, &quadVAO);
    glBindVertexArray(quadVAO);
}

void Sprite::initializeVBO() {
    GLuint vbo;
    GLfloat vertices[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void Sprite::setupVertexAttrib() {
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
}

void Sprite::freeInitializationResources() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Sprite::setShaderInitialUniforms() {
    std::string projectionMatrixName = std::string("projection");
    std::string SpriteSamplerName = std::string("sprite");

    shader.setMatrix4(projectionMatrixName, projectionMatrix);
    shader.setInt(SpriteSamplerName, 0);

    if (userUniforms.find("init") != userUniforms.end()) {
        userUniforms["init"]();
    }
}

void Sprite::draw( Transform& transform) {
    setDrawingUniforms(transform);

    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    if (userUniforms.find("drawing") != userUniforms.end()) {
        userUniforms["drawing"]();
        return;
    }

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    freeDrawingResources();
}

void Sprite::setTintingColor( Color& newColor) {
    tintingColor = newColor;
}

void Sprite::setUseTint(bool useTint) {
    this->useTint = useTint;
}

void Sprite::setUserUniforms(
    std::function<void()> initFunc,
    std::function<void()> initDrawingFunc,
    std::function<void()> drawingFunc) {

    if (!userShader) return;

    if (initFunc) userUniforms["init"] = initFunc;
    if (initDrawingFunc) userUniforms["init_drawing"] = initDrawingFunc;
    if (drawingFunc) userUniforms["drawing"] = drawingFunc;
}

glm::mat4 Sprite::computeModelMatrix(Transform& transform) {
    Vector3 pos = transform.getPosition();
    Vector3 scale = transform.getScale();
    Dimensions2 dimensions = texture.getDimensions();

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(pos.x, pos.y, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * dimensions.width, 0.5f * dimensions.height, 0.0f));
    model = glm::rotate(model, math::degrees_to_radians(transform.getRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * dimensions.width, -0.5f * dimensions.height, 0.0f));
    model = glm::scale(model, glm::vec3(dimensions.width * scale.x, dimensions.height * scale.y, 1.0f));

    return model;
}

void Sprite::setDrawingUniforms( Transform& transform) {
    std::string projectionMatrixName = std::string("projection");
    std::string TintingColorName = std::string("TintingColor");
    std::string useTintName = std::string("useTint");
    std::string modelName = std::string("model");

    glm::mat4 model = computeModelMatrix(transform);

    shader.setMatrix4(projectionMatrixName, projectionMatrix);
    shader.setMatrix4(modelName, model);
    shader.setBool(useTintName, useTint);

    if (userUniforms.find("init_drawing") != userUniforms.end()) {
        userUniforms["init_drawing"]();
    }

    shader.setFloatVec4(TintingColorName,
        tintingColor.r / 255.0f,
        tintingColor.g / 255.0f,
        tintingColor.b / 255.0f,
        alpha ? tintingColor.a / 255.0f : 1.0f);
}

void Sprite::freeDrawingResources() {
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

//void Sprite::system(EntityManager& entityManager) {
//    
//}
