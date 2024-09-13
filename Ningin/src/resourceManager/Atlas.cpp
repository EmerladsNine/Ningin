#include "Atlas.h"
#include "../Ningin.h"
#include "Texture2D.h"
#include <GL/glew.h>
#include <stdexcept>
#include <fstream>
#include <iostream>

Atlas::Atlas(size_t id) : atlasID(0), index(0), id(id)
{
	GenerateAtlas();
}

void Atlas::GenerateAtlas()
{
	glGenTextures(1, &atlasID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, atlasID);
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, 256, 256, ATLAS_LIMIT, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
}

void Atlas::AddSprite(std::filesystem::path& path, std::string& name)
{
	auto img = LoadTexture(path);
	Dimensions2 dimensions(static_cast<int>(img.size()), static_cast<int>(img.size()));

	AddSpriteFromData(img, dimensions, name);
}

void Atlas::AddSpritesWithJson(std::filesystem::path& spriteSheetPath, std::filesystem::path& infoPath)
{
	SpriteSheetInfo info = ParseJson(infoPath);
	AddSprites(spriteSheetPath, info);
}

void Atlas::AddSprites(std::filesystem::path& spriteSheetPath, SpriteSheetInfo& info)
{
	Texture2D texture(spriteSheetPath, true);

	GLuint fbo = GenerateFrameBuffer(texture.GetID());
	for (auto& sprite : info.GetSpriteTiles())
	{
		std::vector<uint8_t> data = GetSpriteTileData(sprite);
		Dimensions2 dimensions = sprite.GetDimensions();
		std::string name = sprite.GetName();
		AddSpriteFromData(data, dimensions, name);
	}

	DeleteFrameBuffer(fbo);
}

void Atlas::AddSpriteFromData(std::vector<uint8_t>& data, Dimensions2& dimensions, std::string& name)
{
	CreateSpriteTexture(dimensions, data);
	SetupSpriteTexture();

	sprites.insert(std::make_pair(name, Sprite{ index, dimensions }));
	++index;
}

GLuint Atlas::GenerateFrameBuffer(GLuint texture)
{
	GLuint fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
	return fbo;
}

std::vector<uint8_t> Atlas::GetSpriteTileData(SpriteTile& sprite)
{
	std::vector<uint8_t> pixels(sprite.GetDimensions().width * sprite.GetDimensions().height * 4);
	glReadPixels(static_cast<GLint>(sprite.GetInSheetPosition().x), static_cast<GLint>(sprite.GetInSheetPosition().y),
		sprite.GetDimensions().width, sprite.GetDimensions().height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
	return pixels;
}

void Atlas::DeleteFrameBuffer(GLuint fbo)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &fbo);
}

std::vector<unsigned char> Atlas::LoadTexture(std::filesystem::path& path)
{
	int width, height, channels;
	std::vector<unsigned char> data;
	unsigned char* imgData = stbi_load(path.string().c_str(), &width, &height, &channels, 4);

	if (!imgData)
	{
		throw std::runtime_error("Failed to load image");
	}

	Dimensions2 dimensions = Dimensions2(width, height);
	data.assign(imgData, imgData + width * height * 4);
	stbi_image_free(imgData);

	return data;
}

void Atlas::SetupSpriteTexture()
{
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Atlas::CreateSpriteTexture(Dimensions2& dimensions, std::vector<uint8_t>& data)
{
	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, index, dimensions.width, dimensions.height, 1, GL_RGBA,
		GL_UNSIGNED_BYTE, data.data());
}

bool Atlas::CanAddSprite()
{
	return index < ATLAS_LIMIT - 1;
}

bool Atlas::CanAddSpriteSheet(SpriteSheetInfo& spriteSheet)
{
	return (index + spriteSheet.GetSpriteTiles().size()) < ATLAS_LIMIT - 1;
}

void Atlas::Unbind()
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void Atlas::Bind()
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, atlasID);
}

SpriteSheetInfo Atlas::ParseJson(std::filesystem::path& infoPath)
{
	std::ifstream jsonFile(infoPath);
	if (!jsonFile.is_open())
	{
		throw std::runtime_error("Failed to open JSON file");
	}

	Json::Value root;
	jsonFile >> root;

	std::vector<SpriteTile> spriteTiles;

	SpriteSheetInfo info(spriteTiles);

	if (root.isMember("spriteTiles"))
	{
		Json::Value& spriteTiles = root["spriteTiles"];
		for (auto& tile : spriteTiles)
		{
			SpriteTile spriteTile(std::string(""), Vector2(), Dimensions2());

			// Populate SpriteTile fields
			spriteTile.SetName(tile["name"].asString());
			spriteTile.SetDimensions(
				Dimensions2(tile["dimensions"]["width"].asInt(), tile["dimensions"]["height"].asInt()));
			spriteTile.SetInSheetPosition(Vector2(static_cast<float>(tile["inSheetPosition"]["x"].asInt()),
				static_cast<float>(tile["inSheetPosition"]["y"].asInt())));

			// Add to the SpriteSheetInfo
			info.AddSpriteTile(spriteTile);
		}
	}

	return info;
}
