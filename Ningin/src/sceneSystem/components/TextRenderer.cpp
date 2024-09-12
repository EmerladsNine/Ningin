#include "TextRenderer.h"
#include "transform.h"
#include <gtc/matrix_transform.hpp>

Text::Text(string& fontName, string& shaderName, Color& textColor, string& text, uint8_t fontSize)
	: shader(resourceManager.GetShader(shaderName)), font(resourceManager.GetFont(fontName)),
	textColor(textColor), text(text), fontSize(fontSize), letterDimensions(48.0f), baseModel(glm::mat4(1.0f)),
	mustCalculate(true), userShader(shaderName != "text"), vao(0), vbo(0)
{
	SetShaderInitialUniforms();
	InitializeRenderData();
}

Text::~Text()
{
	glDeleteVertexArrays(1, &vao);
}

void Text::InitializeRenderData()
{
	CalculateTextDimensions();
	InitializeShaderInfo();
	InitializeVao();
	InitializeVbo();
	SetupVertexAttrib();
	FreeResources(false);
}

void Text::SetShaderInitialUniforms()
{
	string projectionMatrixName = string("projection");
	string TextSamplerName = string("text");

	shader.SetInt(TextSamplerName, 0);
	shader.SetMatrix4(projectionMatrixName, projectionMatrix);

	if (userUniforms.count("init"))
	{
		userUniforms["init"]();
	}
}

void Text::InitializeShaderInfo()
{
	for (int i = 0; i < ARRAY_LIMIT; i++)
	{
		transforms.push_back(glm::mat4(1.0f));
		charsMap.push_back(0);
	}
}

void Text::InitializeVao()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

void Text::InitializeVbo()
{
	float vertexData[] = {
		0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
}

void Text::SetupVertexAttrib()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
}

void Text::FreeResources(bool unbindTexture)
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	if (unbindTexture)
	{
		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	}
}

void Text::ConfigureDrawingContext()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, font.GetFontTexture().GetTextureArray());
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindVertexArray(vao);
}

void Text::Draw(Transform& transform)
{
	SetInitDrawingUniforms();
	ConfigureDrawingContext();

	if (mustCalculate) {
		ComputeTextTransform(transform);
	}

	Vector3 pos = transform.GetPosition();
	float scale = static_cast<float>(fontSize) / 256.0f;
	float hBearing = static_cast<float>(font.GetCharMap().at('H').GetBearing().height);
	int32_t workingIndex = 0;
	float xOffSet = 0.0f;

	for (char c : text) {
		auto& ch = font.GetCharMap().at(c);

		if (c == '\n') {
			pos.y += ch.GetSize().height * 1.3f * scale;
			xOffSet = 0.0f;
		}
		else if (c == ' ') {
			xOffSet += (ch.GetAdvance() >> 6) * scale;
		}
		else {
			float xpos = ch.GetBearing().width * scale;
			float ypos = pos.y + (hBearing - ch.GetBearing().height) * scale;

			transforms[workingIndex] = ComputeLetterTransform(xOffSet, xpos, ypos, letterDimensions);
			charsMap[workingIndex] = ch.GetAsciiIndex();

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

void Text::RenderText(int32_t length)
{
	if (length != 0) {
		SetDrawingUniforms(length);
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, length);
	}
}

void Text::CalculateTextDimensions()
{
	auto [splitedText, longestLine] = GetTextInfo();
	textDimensions.height = static_cast<int32_t>(
		splitedText.size() * fontSize + font.GetCharMap().at('\n').GetSize().height * 1.3f * fontSize / 256.0f);
	textDimensions.width = static_cast<int32_t>(longestLine * fontSize);
}

pair<vector<vector<char>>, size_t> Text::GetTextInfo()
{
	vector<vector<char>> splitedText;
	splitedText.push_back(vector<char>());
	size_t currentLine = 0;
	size_t longestLine = 0;

	for (char c : text) {
		if (c == '\n') {
			if (longestLine < splitedText[currentLine].size()) {
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

void Text::SetInitDrawingUniforms()
{
	string projectionMatrixName = string("projection");
	string TextColorName = string("TextColor");

	shader.SetMatrix4(projectionMatrixName, projectionMatrix);

	if (userUniforms.count("init_drawing")) {
		userUniforms["init_drawing"]();
		return;
	}

	shader.SetFloatVec4(TextColorName, textColor.r / 255.0f, textColor.g / 255.0f, textColor.b / 255.0f,
		textColor.a / 255.0f);
}

void Text::SetDrawingUniforms(int32_t length)
{
	string transformsName = string("Transforms");
	string charsMapName = string("CharsMap");
	shader.SetMatrix4WithLength(transformsName, length, transforms);
	shader.SetIntWithLength(charsMapName, length, charsMap);

	if (userUniforms.count("drawing")) {
		userUniforms["drawing"]();
	}
}

glm::mat4 Text::ComputeLetterTransform(float xOffSet, float xpos, float ypos, float scale)
{
	glm::mat4 letterModel = baseModel;

	letterModel = glm::translate(letterModel, glm::vec3(xOffSet + xpos, ypos, 0.0f));
	letterModel = glm::scale(letterModel, glm::vec3(scale, scale, 1.0f));

	return letterModel;
}

void Text::ComputeTextTransform(Transform& transform)
{
	Vector3 pos = transform.GetPosition();
	float scale = static_cast<float>(fontSize) / 256.0f;

	Vector2 text_center = { textDimensions.width * scale / 2.0f, textDimensions.height * scale / 2.0f };

	baseModel = glm::translate(baseModel, glm::vec3(pos.x, pos.y, 0.0f));
	baseModel = glm::translate(baseModel, glm::vec3(text_center.x, text_center.y, 0.0f));
	baseModel = glm::rotate(baseModel, transform.GetRotation().z, glm::vec3(0.0f, 0.0f, 1.0f));
	baseModel = glm::translate(baseModel, glm::vec3(-text_center.x, -text_center.y, 0.0f));

	mustCalculate = false;
}

void Text::SetUserUniforms(function<void()> initFunc, function<void()> initDrawingFunc,
	function<void()> drawingFunc)
{
	userUniforms["init"] = initFunc;
	userUniforms["init_drawing"] = initDrawingFunc;
	userUniforms["drawing"] = drawingFunc;
}

void Text::SetTextColor(Color& newColor)
{
	textColor = newColor;
}

void Text::SetText(string& text)
{
	this->text = text;
	mustCalculate = true;
}

void Text::SetFontSize(uint8_t fontSize)
{
	this->fontSize = fontSize;
	mustCalculate = true;
}

void Text::System(EntityManager* entityManager) 
{
	auto& transformArchetypeMap = entityManager->archetypeManager.componentIndex[typeid(Transform)];
	for (auto& TextArchetype : entityManager->archetypeManager.componentIndex[typeid(Text)]) {
		auto it = transformArchetypeMap.find(TextArchetype.first);

		if (it != transformArchetypeMap.end()) {
			size_t textColumn = TextArchetype.second.column;
			size_t transformColumn = it->second.column;

			int row = 0;

			for (void* textData : TextArchetype.second.archetype->components[textColumn]) {
				if (textData == nullptr) {
					return;
				}

				void* transformData = TextArchetype.second.archetype->components[transformColumn][row];
				
				if (transformData == nullptr) {
					return;
				}

				Text* text = static_cast<Text*>(textData);
				Transform* transform = static_cast<Transform*>(transformData);

				text->Draw(*transform);

				row++;
			}
		}
	}
}
