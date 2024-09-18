#include "TextRenderer.h"
#include "transform.h"
#include <gtc/matrix_transform.hpp>
#include <iostream>

TextRenderer::TextRenderer(string& fontName, string& shaderName, Color& textColor, string& text,
	uint8_t fontSize) : _shader(resourceManager.GetShader(shaderName)),
	_font(resourceManager.GetFont(fontName)), _textColor(textColor), _text(text), _fontSize(fontSize),
	_letterDimensions(fontSize), _baseModel(glm::mat4(1.0f)), _mustCalculate(true)
	, _userShader(shaderName != "text"), _vao(0), _vbo(0)
{
	SetShaderInitialUniforms();
	InitializeRenderData();
}


void TextRenderer::InitializeRenderData()
{
	_fontCharsMap = _font.GetCharMap();
	CalculateTextDimensions();
	InitializeShaderInfo();
	InitializeVao();
	InitializeVbo();
	SetupVertexAttrib();
}

void TextRenderer::SetShaderInitialUniforms()
{
	string projectionMatrixName = string("projection");
	string TextSamplerName = string("text");

	_shader.Use();
	_shader.SetInt(TextSamplerName, 0);
	_shader.SetMatrix4(projectionMatrixName, projectionMatrix);

	if (_userUniforms.count("init"))
	{
		_userUniforms["init"]();
	}
}

void TextRenderer::InitializeShaderInfo()
{
	_transforms.resize(ARRAY_LIMIT, glm::mat4(1.0f));
	_textAsciiIndices.resize(ARRAY_LIMIT, 0);
}

void TextRenderer::InitializeVao()
{
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
}

void TextRenderer::InitializeVbo()
{
	float vertexData[] = {
		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
	};

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
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
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, _font.GetFontTexture().GetTextureArray());
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
}

void TextRenderer::Draw(Transform& transform)
{
	_shader.Use();

	SetInitDrawingUniforms();
	ConfigureDrawingContext();

	if (_mustCalculate)
	{
		ComputeTextTransform(transform);
	}

	Vector3 pos = transform.position;
	float scale = float(_fontSize) / 256.0f;
	float hBearing = float(_fontCharsMap.at('H').bearing.height);

	int32_t workingIndex = 0;
	float xOffSet = 0.0f;

	for (char c : _text)
	{
		Character ch = _fontCharsMap[static_cast<unsigned char>(c)];

		if (c == '\n')
		{
			pos.y += float(ch.size.height) * 1.3f * scale;
			xOffSet = 0.0f;
		}
		else if (c == ' ')
		{
			xOffSet += (float(ch.advance >> 6)) * scale;
		}
		else
		{
			float xpos = float(ch.bearing.width) * scale;
			float ypos = pos.y + (hBearing - float(ch.bearing.height)) * scale;

			_transforms[workingIndex] = ComputeLetterTransform(xOffSet, xpos, ypos, _letterDimensions);
			_textAsciiIndices[workingIndex] = ch.asciiIndex;

			if (workingIndex == ARRAY_LIMIT - 1)
			{
				RenderText(workingIndex);
				workingIndex = 0;
			}

			xOffSet += (float(ch.advance >> 6)) * scale;
			workingIndex++;
		}
	}

	RenderText(workingIndex);
	FreeResources(true);
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

void TextRenderer::SetTextColor(Color& color)
{
	_textColor = color;
}

void TextRenderer::SetText(string& text)
{
	this->_text = text;
	CalculateTextDimensions();
	_mustCalculate = true;
}

void TextRenderer::SetFontSize(uint8_t fontSize)
{
	this->_fontSize = fontSize;
	CalculateTextDimensions();
	_letterDimensions = fontSize;
	_mustCalculate = true;
}

void TextRenderer::SetInitDrawingUniforms()
{
	string projectionMatrixName = string("projection");
	string TextColorName = string("TextColor");

	_shader.SetMatrix4(projectionMatrixName, projectionMatrix);

	if (_userUniforms.count("init_drawing"))
	{
		_userUniforms["init_drawing"]();
		return;
	}

	_shader.SetFloatVec4(TextColorName, float(_textColor.r) / 255.0f, float(_textColor.g) / 255.0f,
		float(_textColor.b / 255.0f), float(_textColor.a / 255.0f));
}

void TextRenderer::SetDrawingUniforms(int32_t length)
{
	string transformsName = string("Transforms");
	string charsMapName = string("CharsMap");

	_shader.SetMatrix4WithLength(transformsName, length, _transforms);
	_shader.SetIntWithLength(charsMapName, length, _textAsciiIndices);

	if (_userUniforms.count("drawing"))
	{
		_userUniforms["drawing"]();
	}
}

glm::mat4 TextRenderer::ComputeLetterTransform(float xOffSet, float xpos, float ypos, float scale)
{
	glm::mat4 letterModel = _baseModel;
	//glm::mat4 letterModel = glm::mat4(1.0);

	letterModel = glm::translate(letterModel, glm::vec3(xOffSet + xpos, ypos, 0.0f));
	letterModel = glm::scale(letterModel, glm::vec3(scale, scale, 1.0f));

	return letterModel;
}

void TextRenderer::ComputeTextTransform(Transform& transform)
{
	Vector3 pos = transform.position;

	Vector2 textCenter = { _textDimensions.width / 2.0f, _textDimensions.height / 2.0f };

	_baseModel = glm::translate(_baseModel, glm::vec3(pos.x, pos.y, 0.0f));
	_baseModel = glm::translate(_baseModel, glm::vec3(textCenter.x, textCenter.y, 0.0f));
	_baseModel = glm::rotate(_baseModel, DegreesToRadians(transform.rotation.z),
		glm::vec3(0.0f, 0.0f, 1.0f));

	_baseModel = glm::translate(_baseModel, glm::vec3(-textCenter.x, -textCenter.y, 0.0f));

	_mustCalculate = false;
}

void TextRenderer::SetUserUniforms(function<void()> initFunc, function<void()> initDrawingFunc,
	function<void()> drawingFunc)
{
	_userUniforms["init"] = initFunc;
	_userUniforms["init_drawing"] = initDrawingFunc;
	_userUniforms["drawing"] = drawingFunc;
}

void TextRenderer::System(EntityManager* entityManager) 
{
	auto& transformArchetypeMap = entityManager->archetypeManager.componentIndex[typeid(Transform)];
	for (auto& TextArchetype : entityManager->archetypeManager.componentIndex[typeid(TextRenderer)])
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
	textRenderer.SetTextColor(color);
}

void TextSetText(TextRenderer& textRenderer, string& text)
{
	textRenderer.SetText(text);
}

void TextSetFontSize(TextRenderer& textRenderer, uint8_t fontSize)
{
	textRenderer.SetFontSize(fontSize);
}
