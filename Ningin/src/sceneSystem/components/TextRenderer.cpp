#include "TextRenderer.h"
#include <gtc/matrix_transform.hpp>
#include <iostream>

namespace Ningin::Components
{
	TextRenderer::TextRenderer(string& fontName, string& shaderName, Color& textColor, string& text,
		uint8_t fontSize, bool useMultiLine) : _shader(resourceManager.GetShader(shaderName)),
		_font(resourceManager.GetFont(fontName)), _text(text), _baseModel(glm::mat4(1.0f)), _vbo(Buffer()),
		_vao(VAO()), _mustCalculate(true), _useMultiLine(useMultiLine), _userShader(shaderName != "text")
	{
		InitializeRenderData(textColor, fontSize);
	}

	void TextRenderer::InitializeRenderData(Color& color, uint8_t fontSize)
	{
		_fontCharsMap = _font.GetCharMap();

		SetShaderInitialUniforms(color, fontSize);

		CalculateTextDimensions();
		SplitText();
		CalculateWordsWidth();

		InitializeShaderInfo();

		InitializeVbo();
		SetupVertexAttrib();

		_shouldCheckWord = true;
	}

	void TextRenderer::SetShaderInitialUniforms(Color& color, uint8_t fontSize)
	{
		_shader.Use();

		SetTextColor(color, false);
		SetFontSize(fontSize, false);

		if (_userUniforms.count("init"))
		{
			_userUniforms["init"]();
		}
	}

	void TextRenderer::InitializeShaderInfo()
	{
		_lettersPositions.resize(ARRAY_LIMIT / sizeof(glm::mat4), glm::vec2(0, 0));
		_textAsciiIndices.resize(ARRAY_LIMIT / sizeof(glm::mat4), 0);
	}

	void TextRenderer::InitializeVbo()
	{
		float vertexData[] = {
			0.0f, 1.0f,
			1.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 0.0f,
		};

		_vbo = Buffer(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	}

	void TextRenderer::SetupVertexAttrib()
	{
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	}

	void TextRenderer::FreeResources(bool unbindTexture)
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		if (unbindTexture)
		{
			glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
		}
	}

	void TextRenderer::ConfigureDrawingContext()
	{
		_font.GetFontTexture().Bind();
		_vao.BindVAO();
	}

	void TextRenderer::SplitText() {
		istringstream stream(_text);
		string word;

		// Use stringstream to split the input text by spaces
		while (stream >> word) {
			_words.push_back(word);
		}
	}

	void TextRenderer::IndentNewLine(Vector3* position, float* xOffSet, bool checkWord)
	{
		position->y += float(_fontCharsMap.at('\n').size.height) * 1.3f * _scale;
		*xOffSet = 0.0f;
		_shouldCheckWord = checkWord;
	}

	float TextRenderer::CalculateWordWidth(string& word)
	{
		float width = 0;

		for (char c : word)
		{
			width += float(((_fontCharsMap.at(c).size.width +
				static_cast<unsigned int>(_fontCharsMap.at(c).advance)) >> 6)) * _scale;
		}

		return width;
	}

	void TextRenderer::Draw(Transform& transform)
	{
		_shader.Use();

		SetInitDrawingUniforms(transform);
		ConfigureDrawingContext();

		if (_mustCalculate || (Vector3NotEqual(_transform.position, transform.position)
			&& _transform.rotation.z != transform.rotation.z))
		{
			ComputeTextTransform(transform);
			_transform = transform;
		}

		Vector3 pos = transform.position;
		float hBearing = float(_fontCharsMap.at('H').bearing.height);

		int workingIndex = 0;
		int wordIndex = 0;
		int letterIndex = 0;

		float xOffSet = 0.0f;
		float xpos = 0;
		float ypos = 0;

		for (char c : _text)
		{
			Character ch = _fontCharsMap[static_cast<unsigned char>(c)];

			if (c == '\n')
			{
				IndentNewLine(&pos, &xOffSet, true);
				wordIndex++;
			}
			else if (c == ' ')
			{
				if (_text[letterIndex + 1] != ' ')
					wordIndex++;

				_shouldCheckWord = true;
				xOffSet += float(static_cast<unsigned int>(ch.advance) >> 6) * _scale;
			}
			else
			{
				float xpos = pos.x + float(ch.bearing.width) * _scale;

				if (_shouldCheckWord && _useMultiLine && xOffSet + _wordsWidth[wordIndex]
					>= float(windowDimensions.width))
				{
					IndentNewLine(&pos, &xOffSet, false);
				}

				float ypos = pos.y + (hBearing - float(ch.bearing.height)) * _scale;

				_lettersPositions[workingIndex] = glm::vec2(xOffSet + xpos, ypos);
				_textAsciiIndices[workingIndex] = ch.asciiIndex;

				if (workingIndex == ARRAY_LIMIT - 1)
				{
					RenderText(workingIndex);
					workingIndex = 0;
				}

				xOffSet += float(static_cast<unsigned int>(ch.advance) >> 6) * _scale;
				_shouldCheckWord = false;
				workingIndex++;
			}

			letterIndex++;
		}

		RenderText(workingIndex);
		glBindVertexArray(0);
	}

	void TextRenderer::RenderText(int32_t length)
	{
		if (length != 0)
		{
			SetDrawingUniforms(length);
			glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, length);
		}
	}

	void TextRenderer::CalculateTextDimensions()
	{
		auto [splitedText, longestLine] = GetTextInfo();

		_textDimensions.height = static_cast<unsigned int>(float(splitedText.size())
			* float(_fontSize) + float(_fontCharsMap.at('\n').size.height)
			* 1.3f * (float(_fontSize) / 256.0f));

		_textDimensions.width = static_cast<unsigned int>(static_cast<uint8_t>(longestLine) * _fontSize);
	}

	void TextRenderer::CalculateWordsWidth()
	{
		for (string word : _words)
		{
			float width = 0;

			for (char c : word)
			{
				width += float(((_fontCharsMap.at(c).size.width +
					static_cast<unsigned int>(_fontCharsMap.at(c).advance)) >> 6)) * _scale;
			}

			_wordsWidth.push_back(width);
		}
	}

	pair<vector<vector<char>>, size_t> TextRenderer::GetTextInfo()
	{
		vector<vector<char>> splitedText(1);
		size_t currentLine = 0;
		size_t longestLine = 0;

		for (char c : _text)
		{
			if (c == '\n')
			{
				if (splitedText.back().size() > longestLine)
				{
					longestLine = splitedText.back().size();
				}

				splitedText.emplace_back();
				continue;
			}

			splitedText.back().push_back(c);
		}

		return { splitedText, longestLine };
	}

	void TextRenderer::SetTextColor(Color& color, bool use)
	{
		if (_textColor == color) return;

		_textColor = color;

		if (use) _shader.Use();
		_shader.SetFloatVec4("TextColor", float(_textColor.r) / 255.0f, float(_textColor.g) / 255.0f,
			float(_textColor.b / 255.0f), float(_textColor.a / 255.0f));
	}

	void TextRenderer::SetText(string& text)
	{
		this->_text = text;
		CalculateTextDimensions();
		SplitText();
		CalculateWordsWidth();
		_mustCalculate = true;
	}

	void TextRenderer::SetFontSize(uint8_t fontSize, bool use)
	{
		if (_fontSize == fontSize) return;

		_fontSize = fontSize;
		_scale = float(_fontSize) / 256.0f;

		CalculateTextDimensions();
		CalculateWordsWidth();

		_shader.SetFloat("scale", fontSize);
		_mustCalculate = true;
	}

	void TextRenderer::SetFont(const string& fontName)
	{
		try
		{
			_font = resourceManager.GetFont(fontName);
			_fontCharsMap = _font.GetCharMap();
			SetFontSize(_fontSize, true);
		}
		catch (exception e)
		{
			// Todo send warning
			return;
		}
	}

	void TextRenderer::SetInitDrawingUniforms(Transform& transform)
	{
		if (_userUniforms.count("init_drawing"))
		{
			_userUniforms["init_drawing"]();
			return;
		}
	}

	void TextRenderer::SetDrawingUniforms(int32_t length)
	{
		_shader.SetFloatVec2WithLength("lettersPositions", length, _lettersPositions);
		_shader.SetIntWithLength("charsMap", length, _textAsciiIndices);

		if (_userUniforms.count("drawing"))
		{
			_userUniforms["drawing"]();
		}
	}

	void TextRenderer::ComputeTextTransform(Transform& transform)
	{
		Vector3 pos = transform.position;
		_baseModel = glm::mat4(1.0f);

		Vector2 textCenter = { _textDimensions.width / 2.0f, _textDimensions.height / 2.0f };

		_baseModel = glm::translate(_baseModel, glm::vec3(pos.x, pos.y, 0.0f));
		_baseModel = glm::translate(_baseModel, glm::vec3(textCenter.x, textCenter.y, 0.0f));
		_baseModel = glm::rotate(_baseModel, DegreesToRadians(transform.rotation.z),
			glm::vec3(0.0f, 0.0f, 1.0f));

		_baseModel = glm::translate(_baseModel, glm::vec3(-textCenter.x, -textCenter.y, 0.0f));
		_baseModel = glm::translate(_baseModel, glm::vec3(-pos.x, -pos.y, 0.0f));

		_shader.SetMatrix4("baseModel", _baseModel);
		_mustCalculate = false;
	}

	void TextRenderer::SetUserUniforms(function<void()> initFunc, function<void()> initDrawingFunc,
		function<void()> drawingFunc)
	{
		_userUniforms["init"] = initFunc;
		_userUniforms["init_drawing"] = initDrawingFunc;
		_userUniforms["drawing"] = drawingFunc;
	}

	void TextRenderer::System(ArchetypeManager& archetypeManager)
	{
		auto& transformArchetypeMap = archetypeManager.componentIndex[typeid(Transform)];
		for (auto& TextArchetype : archetypeManager.componentIndex[typeid(TextRenderer)])
		{
			auto it = transformArchetypeMap.find(TextArchetype.first);

			if (it != transformArchetypeMap.end())
			{
				size_t textColumn = TextArchetype.second.column;
				size_t transformColumn = it->second.column;
				int row = 0;

				for (void* textData : TextArchetype.second.archetype->components[textColumn])
				{
					if (textData == nullptr)
					{
						return;
					}

					void* transformData = TextArchetype.second.archetype->components[transformColumn][row];

					if (transformData == nullptr)
					{
						return;
					}

					TextRenderer* text = static_cast<TextRenderer*>(textData);
					Transform* transform = static_cast<Transform*>(transformData);

					text->Draw(*transform);

					row++;
				}
			}
		}
	}

	void TextSetTextColor(TextRenderer& textRenderer, Color& color)
	{
		textRenderer.SetTextColor(color, true);
	}

	void TextSetText(TextRenderer& textRenderer, string& text)
	{
		textRenderer.SetText(text);
	}

	void TextSetFontSize(TextRenderer& textRenderer, uint8_t fontSize)
	{
		textRenderer.SetFontSize(fontSize, true);
	}

	void TextSetFont(TextRenderer& textRenderer, const string& fontName)
	{
		textRenderer.SetFont(fontName);
	}
}