#pragma once

#include "../../math/math.h"
#include "../../ningin.h"
#include "../../resource_manager/color.h"
#include "../../resource_manager/shader.h"
#include "../../resource_manager/texture2d.h"
#include "transform.h"
#include <GL/glew.h>
#include <functional>
#include <glm.hpp>
#include <memory>
#include <string>
#include <unordered_map>

class SpriteRenderer
{
public:
	SpriteRenderer(std::string& textureName, std::string& shaderName, Color& tintingColor, bool useTint, bool alpha);
	~SpriteRenderer();

	void draw(Transform& transform);
	void setTintingColor(Color& newColor);
	void setUseTint(bool useTint);
	void setUserUniforms(std::function<void()> initFunc, std::function<void()> initDrawingFunc,
		std::function<void()> drawingFunc);

	// static void system(EntityManager& entityManager);

private:
	bool alpha;
	Shader shader;
	Texture2D texture;
	Color tintingColor;
	bool useTint;
	bool userShader;
	std::unordered_map<std::string, std::function<void()>> userUniforms;
	GLuint quadVAO;

	void initializeRenderData();
	void initializeVAO();
	void initializeVBO();
	void setupVertexAttrib();
	void freeInitializationResources();
	void setShaderInitialUniforms();
	void setDrawingUniforms(Transform& transform);
	void freeDrawingResources();
	glm::mat4 computeModelMatrix(Transform& transform);
};
