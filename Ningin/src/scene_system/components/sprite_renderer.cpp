#include "sprite_renderer.h"

SpriteRenderer::SpriteRenderer(std::string &textureName, std::string &shaderName, Color &tintingColor, bool useTint,
                               bool alpha)
    : alpha(alpha), shader(resourceManager.getShader(shaderName)), texture(resourceManager.getTexture(textureName)),
      tintingColor(tintingColor), useTint(useTint), userShader(shaderName != "sprite"), quadVAO(0)
{
    initializeRenderData();
    setShaderInitialUniforms();
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &quadVAO);
}

void SpriteRenderer::initializeRenderData()
{
    initializeVAO();
    initializeVBO();
    setupVertexAttrib();
    freeInitializationResources();
}

void SpriteRenderer::initializeVAO()
{
    glGenVertexArrays(1, &quadVAO);
    glBindVertexArray(quadVAO);
}

void SpriteRenderer::initializeVBO()
{
    GLuint vbo;
    GLfloat vertices[] = {0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f};

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void SpriteRenderer::setupVertexAttrib()
{
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
}

void SpriteRenderer::freeInitializationResources()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteRenderer::setShaderInitialUniforms()
{
    std::string projectionMatrixName = std::string("projection");
    std::string SpriteSamplerName = std::string("sprite");

    shader.setMatrix4(projectionMatrixName, projectionMatrix);
    shader.setInt(SpriteSamplerName, 0);

    if (userUniforms.find("init") != userUniforms.end())
    {
        userUniforms["init"]();
    }
}

void SpriteRenderer::draw(Transform &transform)
{
    setDrawingUniforms(transform);

    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    if (userUniforms.find("drawing") != userUniforms.end())
    {
        userUniforms["drawing"]();
        return;
    }

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    freeDrawingResources();
}

void SpriteRenderer::setTintingColor(Color &newColor)
{
    tintingColor = newColor;
}

void SpriteRenderer::setUseTint(bool useTint)
{
    this->useTint = useTint;
}

void SpriteRenderer::setUserUniforms(std::function<void()> initFunc, std::function<void()> initDrawingFunc,
                                     std::function<void()> drawingFunc)
{
    if (!userShader)
        return;

    if (initFunc)
        userUniforms["init"] = initFunc;
    if (initDrawingFunc)
        userUniforms["init_drawing"] = initDrawingFunc;
    if (drawingFunc)
        userUniforms["drawing"] = drawingFunc;
}

glm::mat4 SpriteRenderer::computeModelMatrix(Transform &transform)
{
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

void SpriteRenderer::setDrawingUniforms(Transform &transform)
{
    std::string projectionMatrixName = std::string("projection");
    std::string TintingColorName = std::string("TintingColor");
    std::string useTintName = std::string("useTint");
    std::string modelName = std::string("model");

    glm::mat4 model = computeModelMatrix(transform);

    shader.setMatrix4(projectionMatrixName, projectionMatrix);
    shader.setMatrix4(modelName, model);
    shader.setBool(useTintName, useTint);

    if (userUniforms.find("init_drawing") != userUniforms.end())
    {
        userUniforms["init_drawing"]();
    }

    shader.setFloatVec4(TintingColorName, tintingColor.r / 255.0f, tintingColor.g / 255.0f, tintingColor.b / 255.0f,
                        alpha ? tintingColor.a / 255.0f : 1.0f);
}

void SpriteRenderer::freeDrawingResources()
{
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

// void Sprite::system(EntityManager& entityManager) {
//
// }
