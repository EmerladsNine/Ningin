#include "SpriteRenderer.h"

namespace Ningin::Components
{
	SpriteRenderer::SpriteRenderer(string& textureName, string& shaderName, Color& tintingColor,
		bool useTint, bool alpha) : _alpha(alpha), _shader(resourceManager.GetShader(shaderName)),
		_quadVAO(VAO()), _texture(resourceManager.GetTexture(textureName)), _userShader(shaderName != "sprite")
	{
		InitializeRenderData();
		SetShaderInitialUniforms(tintingColor, useTint);
	}

	void SpriteRenderer::InitializeRenderData()
	{
		InitializeVBO();
		SetupVertexAttrib();
		FreeInitializationResources();
	}

	void SpriteRenderer::InitializeVBO()
	{
		GLfloat vertices[] = { 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
							  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f };

		Buffer vbo(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
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

	void SpriteRenderer::SetShaderInitialUniforms(Color& color, bool useTint)
	{
		_shader.Use();

		SetTintingColor(color, false);
		SetUseTint(useTint, false);

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

		_quadVAO.BindVAO();
		glDrawArrays(GL_TRIANGLES, 0, 6);

		FreeDrawingResources();
	}

	void SpriteRenderer::SetTintingColor(Color& color, bool use)
	{
		if (_tintingColor == color) return;

		_tintingColor = color;

		if (use) _shader.Use();
		_shader.SetFloatVec4("TintingColor", _tintingColor.r / 255.0f, _tintingColor.g / 255.0f,
			_tintingColor.b / 255.0f, _alpha ? _tintingColor.a / 255.0f : 1.0f);
	}

	void SpriteRenderer::SetUseTint(bool useTint, bool use)
	{
		if (_useTint == useTint) return;

		_useTint = useTint;

		if (use) _shader.Use();
		_shader.SetBool("useTint", _useTint);
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
		glm::mat4 model = ComputeModelMatrix(transform);

		_shader.Use();
		_shader.SetMatrix4("model", model);

		if (_userUniforms.find("init_drawing") != _userUniforms.end())
		{
			_userUniforms["init_drawing"]();
		}
	}

	void SpriteRenderer::FreeDrawingResources()
	{
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void SpriteRenderer::System()
	{
		auto& transformArchetypeMap = EntityManager::archetypeManager.componentIndex[typeid(Transform)];

		for (auto& SpriteArchetype : EntityManager::archetypeManager.componentIndex[typeid(SpriteRenderer)])
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
		spriteRenderer.SetTintingColor(color, true);
	}

	void SpriteSetUseTint(SpriteRenderer& spriteRenderer, bool useTint)
	{
		spriteRenderer.SetUseTint(useTint, true);
	}
}