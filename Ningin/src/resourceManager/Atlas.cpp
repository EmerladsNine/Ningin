#include "Atlas.h"
#include "../Ningin.h"
#include "Texture2D.h"
#include <GL/glew.h>
#include <stdexcept>
#include <fstream>
#include <iostream>

Atlas::Atlas(size_t id) : _atlasID(0), _index(0), _id(id)
{
	GenerateAtlas();
}

void Atlas::GenerateAtlas()
{
	glGenTextures(1, &_atlasID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, _atlasID);
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, 256, 256, ATLAS_LIMIT, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
}

void Atlas::AddSprite(const filesystem::path& path, string& name)
{
	auto img = LoadTexture(path);
	Dimensions2 dimensions(static_cast<int>(img.size()), static_cast<int>(img.size()));

	AddSpriteFromData(img, dimensions, name);
}

void Atlas::AddSpritesWithJson(filesystem::path& spriteSheetPath, filesystem::path& infoPath)
{
	SpriteSheetInfo info = ParseJson(infoPath);
	AddSprites(spriteSheetPath, info);
}

void Atlas::AddSprites(filesystem::path& spriteSheetPath, SpriteSheetInfo& info)
{
	Texture2D texture(spriteSheetPath, true);

	GLuint fbo = GenerateFrameBuffer(texture.GetID());
	for (auto& sprite : info.GetSpriteTiles())
	{
		vector<uint8_t> data = GetSpriteTileData(sprite);
		Dimensions2 dimensions = sprite.GetDimensions();
		string name = sprite.GetName();
		AddSpriteFromData(data, dimensions, name);
	}

	DeleteFrameBuffer(fbo);
}

void Atlas::AddSpriteFromData(vector<uint8_t>& data, Dimensions2& dimensions, string& name)
{
	CreateSpriteTexture(dimensions, data);
	SetupSpriteTexture();

	_sprites.insert(make_pair(name, Sprite{ _index, dimensions }));
	++_index;
}

GLuint Atlas::GenerateFrameBuffer(GLuint texture)
{
	GLuint fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
	return fbo;
}

vector<uint8_t> Atlas::GetSpriteTileData(SpriteTile& sprite)
{
	vector<uint8_t> pixels(sprite.GetDimensions().width * sprite.GetDimensions().height * 4);

	glReadPixels(static_cast<GLint>(sprite.GetInSheetPosition().x), static_cast<GLint>(sprite
		.GetInSheetPosition().y), sprite.GetDimensions().width, sprite.GetDimensions().height, GL_RGBA,
		GL_UNSIGNED_BYTE, pixels.data());

	return pixels;
}

void Atlas::DeleteFrameBuffer(GLuint fbo)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &fbo);
}

vector<unsigned char> Atlas::LoadTexture(const filesystem::path& path)
{
	int width, height, channels;
	vector<unsigned char> data;
	unsigned char* imgData = stbi_load(path.string().c_str(), &width, &height, &channels, 4);

	if (!imgData)
	{
		throw runtime_error("Failed to load image");
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

void Atlas::CreateSpriteTexture(Dimensions2& dimensions, vector<uint8_t>& data)
{
	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, _index, dimensions.width, dimensions.height, 1, GL_RGBA,
		GL_UNSIGNED_BYTE, data.data());
}

bool Atlas::CanAddSprite()
{
	return _index < ATLAS_LIMIT - 1;
}

bool Atlas::CanAddSpriteSheet(SpriteSheetInfo& spriteSheet)
{
	return (_index + spriteSheet.GetSpriteTiles().size()) < ATLAS_LIMIT - 1;
}

void Atlas::Unbind()
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void Atlas::Bind()
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, _atlasID);
}

SpriteSheetInfo Atlas::ParseJson(filesystem::path& infoPath)
{
	ifstream jsonFile(infoPath);
	if (!jsonFile.is_open())
	{
		throw runtime_error("Failed to open JSON file");
	}

	Json::Value root;
	jsonFile >> root;

	vector<SpriteTile> spriteTiles;

	SpriteSheetInfo info(spriteTiles);

	if (root.isMember("spriteTiles"))
	{
		Json::Value& spriteTiles = root["spriteTiles"];
		for (auto& tile : spriteTiles)
		{
			SpriteTile spriteTile(string(""), Vector2(), Dimensions2());

			Dimensions2 dimensions = Dimensions2(tile["dimensions"]["width"].asInt(),
				tile["dimensions"]["height"].asInt());

			Vector2 pos = Vector2(static_cast<float>(tile["inSheetPosition"]["x"].asInt()),
				static_cast<float>(tile["inSheetPosition"]["y"].asInt()));

			string name = tile["name"].asString();

			// Populate SpriteTile fields
			spriteTile.SetName(name);
			spriteTile.SetDimensions(dimensions);
			spriteTile.SetInSheetPosition(pos);

			// Add to the SpriteSheetInfo
			info.AddSpriteTile(spriteTile);
		}
	}

	return info;
}
