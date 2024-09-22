#pragma once

#include "../../resourceManager/ResourceManager.h"
#include "../../resourceManager/shader/Shader.h"
#include "../../resourceManager/opengl/buffer.h"
#include "../../resourceManager/color/Color.h"
#include "../../resourceManager/opengl/vao.h"
#include "../../resourceManager/font/Font.h"
#include "../../math/dimensions2.h"
#include "../../math/vector2.h"
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

class TextRenderer
{
	public:
		TextRenderer(string& fontName, string& shaderName, Color& textColor, string& text, uint8_t fontSize,
			bool useMultiLine);

		void SetTextColor(Color& color, bool use);
		void SetFontSize(uint8_t fontSize, bool use);
		void SetFont(const string& fontName);
		void SetText(string& text);

		// ToDo further testing and enchancing then linking it to c#
		void SetUserUniforms(function<void()> initFunc, function<void()> initDrawingFunc,
			function<void()> drawingFunc);

		static void System(EntityManager* entityManager);
		void Draw(Transform& transform);

	private:
		void InitializeRenderData();
		void InitializeShaderInfo();
		void InitializeVbo();

		void SetDrawingUniforms(int32_t length);
		void SetShaderInitialUniforms();
		void SetInitDrawingUniforms(Transform& transform);

		void SetupVertexAttrib();

		void FreeResources(bool unbindTexture);

		glm::mat4 ComputeLetterTransform(float xOffSet, float xpos, float ypos, float scale);
		pair<vector<vector<char>>, size_t> GetTextInfo();
		void ComputeTextTransform(Transform& transform);
		float CalculateWordWidth(string& word);
		void CalculateTextDimensions();
		void CalculateWordsWidth();
		void SplitText();

		void ConfigureDrawingContext();
		void IndentNewLine(Vector3* position, float* xOffSet, bool CheckWord);
		void RenderText(int32_t length);

		unordered_map<string, function<void()>> _userUniforms;
		//vector<glm::mat4> _transforms;
		vector<glm::vec2> _lettersPositions;
		vector<int32_t> _textAsciiIndices;
		unordered_map<GLchar, Character> _fontCharsMap;
		Dimensions2 _textDimensions;
		float _letterDimensions;
		glm::mat4 _baseModel;
		bool _mustCalculate;
		bool _useMultiLine;
		vector<float> _wordsWidth;
		vector<string> _words;
		float _scale;
		string _text;
		uint8_t _fontSize;
		Color _textColor;
		bool _userShader;
		bool _shouldCheckWord;
		Shader _shader;
		VAO _vao;
		Buffer _vbo;
		Font _font;
};

void TextSetTextColor(TextRenderer& textRenderer, Color& color);
void TextSetText(TextRenderer& textRenderer, string& text);
void TextSetFontSize(TextRenderer& textRenderer, uint8_t fontSize);
void SetFont(TextRenderer& textRenderer, const string& fontName);
