#pragma once

#include "../../resource_manager/Texture2D.h"
#include "../../resource_manager/Shader.h"
#include "../../resource_manager/Color.h"
#include "../../math/Math.h"
#include "../../Ningin.h"
#include <unordered_map>
#include "transform.h"
#include <functional>
#include <GL/glew.h>
#include <glm.hpp>
#include <memory>
#include <string>

using namespace std;

class SpriteRenderer
{
public:
	SpriteRenderer(string& textureName, string& shaderName, Color& tintingColor, bool usetint, bool alpha);
	~SpriteRenderer();

	void SetTintingColor(Color& newColor);
	void SetUseTint(bool uSetint);

	void SetUserUniforms(function<void()> initFunc, function<void()> initDrawingFunc,
		function<void()> drawingFunc);

	static void System(EntityManager* entityManager);
	void Draw(Transform& transform);

private:
	void InitializeRenderData();
	void InitializeVAO();
	void InitializeVBO();

	void SetDrawingUniforms(Transform& transform);
	void SetShaderInitialUniforms();

	void SetupVertexAttrib();

	glm::mat4 ComputeModelMatrix(Transform& transform);

	void FreeInitializationResources();
	void FreeDrawingResources();

	unordered_map<string, function<void()>> userUniforms;
	Color tintingColor;
	Texture2D texture;
	bool userShader;
	GLuint quadVAO;
	Shader shader;
	bool usetint;
	bool alpha;
};
