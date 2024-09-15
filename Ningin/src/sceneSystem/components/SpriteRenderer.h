#pragma once

#include "../../resourceManager/Texture2D.h"
#include "../../resourceManager/Shader.h"
#include "../../resourceManager/Color.h"
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

		unordered_map<string, function<void()>> _userUniforms;
		Color _tintingColor;
		Texture2D _texture;
		bool _userShader;
		GLuint _quadVAO;
		Shader _shader;
		bool _useTint;
		bool _alpha;
};
