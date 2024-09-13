#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(string& textureName, string& shaderName, Color& tintingColor,
	bool uSetint, bool alpha) : alpha(alpha), shader(resourceManager.GetShader(shaderName)), quadVAO(0),
	texture(resourceManager.GetTexture(textureName)), tintingColor(tintingColor), usetint(usetint),
	userShader(shaderName != "sprite")
{
	InitializeRenderData();
	SetShaderInitialUniforms();
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &quadVAO);
}

void SpriteRenderer::InitializeRenderData()
{
	InitializeVAO();
	InitializeVBO();
	SetupVertexAttrib();
	FreeInitializationResources();
}

void SpriteRenderer::InitializeVAO()
{
	glGenVertexArrays(1, &quadVAO);
	glBindVertexArray(quadVAO);
}

void SpriteRenderer::InitializeVBO()
{
	GLuint vbo;
	GLfloat vertices[] = { 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
						  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f };

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void SpriteRenderer::SetupVertexAttrib()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
}

void SpriteRenderer::FreeInitializationResources()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void SpriteRenderer::SetShaderInitialUniforms()
{
	string projectionMatrixName = string("projection");
	string SpriteSamplerName = string("sprite");

	shader.SetMatrix4(projectionMatrixName, projectionMatrix);
	shader.SetInt(SpriteSamplerName, 0);

	if (userUniforms.find("init") != userUniforms.end()) {
		userUniforms["init"]();
	}
}

void SpriteRenderer::Draw(Transform& transform)
{
	SetDrawingUniforms(transform);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	if (userUniforms.find("drawing") != userUniforms.end())
	{
		userUniforms["drawing"]();
		return;
	}

	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	FreeDrawingResources();
}

void SpriteRenderer::SetTintingColor(Color& newColor)
{
	tintingColor = newColor;
}

void SpriteRenderer::SetUseTint(bool ustint)
{
	this->usetint = usetint;
}

void SpriteRenderer::SetUserUniforms(function<void()> initFunc, function<void()> initDrawingFunc,
	function<void()> drawingFunc)
{
	if (!userShader) return;

	if (initFunc) userUniforms["init"] = initFunc;

	if (initDrawingFunc) userUniforms["init_drawing"] = initDrawingFunc;

	if (drawingFunc) userUniforms["drawing"] = drawingFunc;
}

glm::mat4 SpriteRenderer::ComputeModelMatrix(Transform& transform)
{
	Vector3 pos = transform.GetPosition();
	Vector3 scale = transform.GetScale();
	Dimensions2 dimensions = texture.GetDimensions();

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(pos.x, pos.y, 0.0f));
	model = glm::translate(model, glm::vec3(0.5f * dimensions.width, 0.5f * dimensions.height, 0.0f));
	model = glm::rotate(model, DegreesToRadians(transform.GetRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * dimensions.width, -0.5f * dimensions.height, 0.0f));
	model = glm::scale(model, glm::vec3(dimensions.width * scale.x, dimensions.height * scale.y, 1.0f));

	return model;
}

void SpriteRenderer::SetDrawingUniforms(Transform& transform)
{
	string projectionMatrixName = string("projection");
	string TintingColorName = string("TintingColor");
	string usetintName = string("usetint");
	string modelName = string("model");

	glm::mat4 model = ComputeModelMatrix(transform);

	shader.SetMatrix4(projectionMatrixName, projectionMatrix);
	shader.SetMatrix4(modelName, model);
	shader.SetBool(usetintName, usetint);

	if (userUniforms.find("init_drawing") != userUniforms.end())
	{
		userUniforms["init_drawing"]();
	}

	shader.SetFloatVec4(TintingColorName, tintingColor.r / 255.0f, tintingColor.g / 255.0f, tintingColor.b / 255.0f,
		alpha ? tintingColor.a / 255.0f : 1.0f);
}

void SpriteRenderer::FreeDrawingResources()
{
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void SpriteRenderer::System(EntityManager* entityManager) 
{
	auto& transformArchetypeMap = entityManager->archetypeManager.componentIndex[typeid(Transform)];

	for (auto& SpriteArchetype : entityManager->archetypeManager.componentIndex[typeid(SpriteRenderer)]) {
		auto it = transformArchetypeMap.find(SpriteArchetype.first);

		if (it != transformArchetypeMap.end()) {
			size_t spriteColumn = SpriteArchetype.second.column;
			size_t transformColumn = it->second.column;

			int row = 0;

			for (void* spriteData : SpriteArchetype.second.archetype->components[spriteColumn]) {
				if (spriteData == nullptr) {
					return;
				}

				void* transformData = SpriteArchetype.second.archetype->components[transformColumn][row];

				if (transformData == nullptr) {
					return;
				}

				SpriteRenderer* sprite = static_cast<SpriteRenderer*>(spriteData);
				Transform* transform = static_cast<Transform*>(transformData);

				sprite->Draw(*transform);

				row++;
			}
		}
	}
}
