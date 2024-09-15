#include "TextRenderer.h"
#include "transform.h"
#include <gtc/matrix_transform.hpp>
#include <iostream>

TextRenderer::TextRenderer(string& fontName, string& shaderName, Color& textColor, string& text,
	uint8_t fontSize) : _shader(resourceManager.GetShader(shaderName)),
	_font(resourceManager.GetFont(fontName)), _textColor(textColor), _text(text), _fontSize(fontSize),
	_letterDimensions(48.0f), _baseModel(glm::mat4(1.0f)), _mustCalculate(true)
	, _userShader(shaderName != "text"), _vao(0), _vbo(0)
{
	SetShaderInitialUniforms();
	InitializeRenderData();
}

void TextRenderer::InitializeRenderData()
{
	CalculateTextDimensions();
	InitializeShaderInfo();
	InitializeVao();
	InitializeVbo();
	SetupVertexAttrib();
	FreeResources(false);
}

void TextRenderer::SetShaderInitialUniforms()
{
	string projectionMatrixName = string("projection");
	string TextSamplerName = string("text");

	_shader.SetInt(TextSamplerName, 0);
	_shader.SetMatrix4(projectionMatrixName, projectionMatrix);

	if (_userUniforms.count("init"))
	{
		_userUniforms["init"]();
	}
}

void TextRenderer::InitializeShaderInfo()
{
	for (int i = 0; i < ARRAY_LIMIT; i++)
	{
		_transforms.push_back(glm::mat4(1.0f));
		_charsMap.push_back(0);
	}
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
		0.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
	};

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
}

void TextRenderer::SetupVertexAttrib()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
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
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBindVertexArray(_vao);
}

void TextRenderer::Draw(Transform& transform)
{
	SetInitDrawingUniforms();
	ConfigureDrawingContext();

	if (_mustCalculate)
	{
		ComputeTextTransform(transform);
	}

	Vector3 pos = transform.GetPosition();
	float scale = static_cast<float>(_fontSize) / 256.0f;
	float hBearing = static_cast<float>(_font.GetCharMap().at('H').GetBearing().height);
	int32_t workingIndex = 0;
	float xOffSet = 0.0f;

	for (char c : _text)
	{
		auto& ch = _font.GetCharMap().at(c);

		if (c == '\n')
		{
			pos.y += ch.GetSize().height * 1.3f * scale;
			xOffSet = 0.0f;
		}
		else if (c == ' ')
		{
			xOffSet += (ch.GetAdvance() >> 6) * scale;
		}
		else
		{
			float xpos = ch.GetBearing().width * scale;
			float ypos = pos.y + (hBearing - ch.GetBearing().height) * scale;

			_transforms[workingIndex] = ComputeLetterTransform(xOffSet, xpos, ypos, _letterDimensions);
			_charsMap[workingIndex] = ch.GetAsciiIndex();

			if (workingIndex == ARRAY_LIMIT - 1)
			{
				RenderText(workingIndex);
				workingIndex = 0;
			}

			xOffSet += (ch.GetAdvance() >> 6) * scale;
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

	_textDimensions.height = static_cast<int32_t>(splitedText.size() * _fontSize + _font.GetCharMap()
		.at('\n').GetSize().height * 1.3f * _fontSize / 256.0f);

	_textDimensions.width = static_cast<int32_t>(longestLine * _fontSize);
}

pair<vector<vector<char>>, size_t> TextRenderer::GetTextInfo()
{
	vector<vector<char>> splitedText;
	splitedText.push_back(vector<char>());
	size_t currentLine = 0;
	size_t longestLine = 0;

	for (char c : _text)
	{
		if (c == '\n')
		{
			if (longestLine < splitedText[currentLine].size())
			{
				longestLine = splitedText[currentLine].size();
			}
			splitedText.push_back(vector<char>());
			currentLine++;
			continue;
		}
		splitedText[currentLine].push_back(c);
	}

	return { splitedText, longestLine };
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

	_shader.SetFloatVec4(TextColorName, _textColor.r / 255.0f, _textColor.g / 255.0f, _textColor.b / 255.0f,
		_textColor.a / 255.0f);
}

void TextRenderer::SetDrawingUniforms(int32_t length)
{
	string transformsName = string("Transforms");
	string charsMapName = string("CharsMap");
	_shader.SetMatrix4WithLength(transformsName, length, _transforms);
	_shader.SetIntWithLength(charsMapName, length, _charsMap);

	if (_userUniforms.count("drawing"))
	{
		_userUniforms["drawing"]();
	}
}

glm::mat4 TextRenderer::ComputeLetterTransform(float xOffSet, float xpos, float ypos, float scale)
{
	glm::mat4 letterModel = _baseModel;

	letterModel = glm::translate(letterModel, glm::vec3(xOffSet + xpos, ypos, 0.0f));
	letterModel = glm::scale(letterModel, glm::vec3(scale, scale, 1.0f));

	return letterModel;
}

void TextRenderer::ComputeTextTransform(Transform& transform)
{
	Vector3 pos = transform.GetPosition();
	float scale = static_cast<float>(_fontSize) / 256.0f;

	Vector2 text_center = { _textDimensions.width * scale / 2.0f, _textDimensions.height * scale / 2.0f };

	_baseModel = glm::translate(_baseModel, glm::vec3(pos.x, pos.y, 0.0f));
	_baseModel = glm::translate(_baseModel, glm::vec3(text_center.x, text_center.y, 0.0f));
	_baseModel = glm::rotate(_baseModel, transform.GetRotation().z, glm::vec3(0.0f, 0.0f, 1.0f));
	_baseModel = glm::translate(_baseModel, glm::vec3(-text_center.x, -text_center.y, 0.0f));

	_mustCalculate = false;
}

void TextRenderer::SetUserUniforms(function<void()> initFunc, function<void()> initDrawingFunc,
	function<void()> drawingFunc)
{
	_userUniforms["init"] = initFunc;
	_userUniforms["init_drawing"] = initDrawingFunc;
	_userUniforms["drawing"] = drawingFunc;
}

void TextRenderer::SetTextColor(Color& newColor)
{
	_textColor = newColor;
}

void TextRenderer::SetText(string& text)
{
	this->_text = text;
	_mustCalculate = true;
}

void TextRenderer::SetFontSize(uint8_t fontSize)
{
	this->_fontSize = fontSize;
	_mustCalculate = true;
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
