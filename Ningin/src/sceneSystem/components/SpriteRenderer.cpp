#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(string& textureName, string& shaderName, Color& tintingColor,
	bool useTint, bool alpha) : _alpha(alpha), _shader(resourceManager.GetShader(shaderName)), _quadVAO(0),
	_texture(resourceManager.GetTexture(textureName)), _tintingColor(tintingColor), _useTint(useTint),
	_userShader(shaderName != "sprite")
{
	InitializeRenderData();
	SetShaderInitialUniforms();
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
	glGenVertexArrays(1, &_quadVAO);
	glBindVertexArray(_quadVAO);
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

	_shader.SetMatrix4(projectionMatrixName, projectionMatrix);
	_shader.SetInt(SpriteSamplerName, 0);

	if (_userUniforms.find("init") != _userUniforms.end())
	{
		_userUniforms["init"]();
	}
}

void SpriteRenderer::Draw(Transform& transform)
{
	SetDrawingUniforms(transform);

	glActiveTexture(GL_TEXTURE0);
	_texture.Bind();

	if (_userUniforms.find("drawing") != _userUniforms.end())
	{
		_userUniforms["drawing"]();
		return;
	}

	glBindVertexArray(_quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	FreeDrawingResources();
}

void SpriteRenderer::SetTintingColor(Color& newColor)
{
	_tintingColor = newColor;
}

void SpriteRenderer::SetUseTint(bool useTint)
{
	this->_useTint = useTint;
}

void SpriteRenderer::SetUserUniforms(function<void()> initFunc, function<void()> initDrawingFunc,
	function<void()> drawingFunc)
{
	if (!_userShader) return;

	if (initFunc) _userUniforms["init"] = initFunc;

	if (initDrawingFunc) _userUniforms["init_drawing"] = initDrawingFunc;

	if (drawingFunc) _userUniforms["drawing"] = drawingFunc;
}

glm::mat4 SpriteRenderer::ComputeModelMatrix(Transform& transform)
{
	Vector3 pos = transform.position;
	Vector3 scale = transform.scale;
	Dimensions2 dimensions = _texture.GetDimensions();

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(pos.x, pos.y, 0.0f));
	model = glm::translate(model, glm::vec3(0.5f * dimensions.width, 0.5f * dimensions.height, 0.0f));
	model = glm::rotate(model, DegreesToRadians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * dimensions.width, -0.5f * dimensions.height, 0.0f));
	model = glm::scale(model, glm::vec3(dimensions.width * scale.x, dimensions.height * scale.y, 1.0f));

	return model;
}

void SpriteRenderer::SetDrawingUniforms(Transform& transform)
{
	string projectionMatrixName = string("projection");
	string TintingColorName = string("TintingColor");
	string usetintName = string("useTint");
	string modelName = string("model");

	glm::mat4 model = ComputeModelMatrix(transform);

	_shader.SetMatrix4(projectionMatrixName, projectionMatrix);
	_shader.SetMatrix4(modelName, model);
	_shader.SetBool(usetintName, _useTint);

	if (_userUniforms.find("init_drawing") != _userUniforms.end())
	{
		_userUniforms["init_drawing"]();
	}

	_shader.SetFloatVec4(TintingColorName, _tintingColor.r / 255.0f, _tintingColor.g / 255.0f,
		_tintingColor.b / 255.0f, _alpha ? _tintingColor.a / 255.0f : 1.0f);
}

void SpriteRenderer::FreeDrawingResources()
{
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void SpriteRenderer::System(EntityManager* entityManager) 
{
	auto& transformArchetypeMap = entityManager->archetypeManager.componentIndex[typeid(Transform)];

	for (auto& SpriteArchetype : entityManager->archetypeManager.componentIndex[typeid(SpriteRenderer)])
	{
		auto it = transformArchetypeMap.find(SpriteArchetype.first);

		if (it != transformArchetypeMap.end())
		{
			size_t spriteColumn = SpriteArchetype.second.column;
			size_t transformColumn = it->second.column;

			int row = 0;

			for (void* spriteData : SpriteArchetype.second.archetype->components[spriteColumn])
			{
				if (spriteData == nullptr)
				{
					return;
				}

				void* transformData = SpriteArchetype.second.archetype->components[transformColumn][row];

				if (transformData == nullptr)
				{
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

void SpriteSetTintingColor(SpriteRenderer& spriteRenderer, Color& color)
{
	spriteRenderer.SetTintingColor(color);
}

void SpriteSetUseTint(SpriteRenderer& spriteRenderer, bool useTint)
{
	spriteRenderer.SetUseTint(useTint);
}
