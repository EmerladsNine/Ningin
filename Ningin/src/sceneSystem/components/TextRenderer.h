#pragma once

#include "../../resourceManager/ResourceManager.h"
#include "../../resourceManager/Shader.h"
#include "../../resourceManager/Color.h"
#include "../../resourceManager/Font.h"
#include "../../math/dimensions2.h"
#include "../../math/math.h"
#include "../../ningin.h"
#include <unordered_map>
#include "transform.h"
#include <functional>
#include <GL/glew.h>
#include <glm.hpp>
#include <string>
#include <vector>

using namespace std;

class Text
{
	public:
		Text(string& fontName, string& shaderName, Color& textColor, string& text, uint8_t fontSize);
		~Text();

		void SetTextColor(Color& newColor);
		void SetFontSize(uint8_t fontSize);
		void SetText(string& text);

		void SetUserUniforms(function<void()> initFunc, function<void()> initDrawingFunc,
			function<void()> drawingFunc);

		static void System(EntityManager* entityManager);
		void Draw(Transform& transform);

	private:
		void InitializeRenderData();
		void InitializeShaderInfo();
		void InitializeVao();
		void InitializeVbo();

		void SetDrawingUniforms(int32_t length);
		void SetShaderInitialUniforms();
		void SetInitDrawingUniforms();

		void SetupVertexAttrib();

		void FreeResources(bool unbindTexture);

		glm::mat4 ComputeLetterTransform(float xOffSet, float xpos, float ypos, float scale);
		pair<vector<vector<char>>, size_t> GetTextInfo();
		void ComputeTextTransform(Transform& transform);
		void CalculateTextDimensions();

		void ConfigureDrawingContext();
		void RenderText(int32_t length);

		unordered_map<string, function<void()>> userUniforms;
		vector<glm::mat4> transforms;
		vector<int32_t> charsMap;
		Dimensions2 textDimensions;
		float letterDimensions;
		glm::mat4 baseModel;
		bool mustCalculate;
		string text;
		uint8_t fontSize;
		Color textColor;
		bool userShader;
		Shader shader;
		GLuint vao;
		GLuint vbo;
		Font font;
};
