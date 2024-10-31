#pragma once

#include "../../resourceManager/texture/Texture2D.h"
#include "../../resourceManager/opengl/buffer.h"
#include "../../resourceManager/shader/Shader.h"
#include "../../resourceManager/color/Color.h"
#include "../../resourceManager/opengl/vao.h"
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

namespace Ningin::Components
{
	class SpriteRenderer
	{
	public:
		SpriteRenderer(string& textureName, string& shaderName, Color& tintingColor, bool usetint, bool alpha);

		void SetTintingColor(Color& color, bool use);
		void SetUseTint(bool useTint, bool use);

		// ToDo further testing and enchancing then linking it to c#
		void SetUserUniforms(function<void()> initFunc, function<void()> initDrawingFunc,
			function<void()> drawingFunc);

		static void System(ArchetypeManager& archetypeManager);
		void Draw(Transform& transform);

	private:
		void InitializeRenderData();
		void InitializeVBO();

		void SetDrawingUniforms(Transform& transform);
		void SetShaderInitialUniforms(Color& color, bool useTint);

		void SetupVertexAttrib();

		glm::mat4 ComputeModelMatrix(Transform& transform);

		void FreeInitializationResources();
		void FreeDrawingResources();

		unordered_map<string, function<void()>> _userUniforms;
		Color _tintingColor;
		Texture2D _texture;
		bool _userShader;
		VAO _quadVAO;
		Shader _shader;
		bool _useTint;
		bool _alpha;
	};

	void SpriteSetTintingColor(SpriteRenderer& spriteRenderer, Color& color);
	void SpriteSetUseTint(SpriteRenderer& spriteRenderer, bool useTint);
}