#pragma once

#include "SpriteSheetInfo.h"
#include <unordered_map>
#include "SpriteTile.h"
#include "Texture2D.h"
#include <json/json.h>
#include <filesystem>
#include <stdexcept>
#include <GL/glew.h>
#include "Sprite.h"
#include <memory>
#include <string>
#include <vector>

class Atlas
{
	public:
		Atlas(size_t id);

		void GenerateAtlas();

		void AddSprite(std::filesystem::path& path, std::string& name);
		void AddSpritesWithJson(std::filesystem::path& spriteSheetPath, std::filesystem::path& infoPath);
		void AddSprites(std::filesystem::path& spriteSheetPath, SpriteSheetInfo& info);
		
		bool CanAddSprite();
		bool CanAddSpriteSheet(SpriteSheetInfo& spriteSheet);

		void Unbind();
		void Bind();

	private:
		std::unordered_map<std::string, Sprite> sprites;
		GLuint atlasID;
		size_t id;

		int index;

		void AddSpriteFromData(std::vector<uint8_t>& data, Dimensions2& dimensions, std::string& name);
		GLuint GenerateFrameBuffer(GLuint texture);
		std::vector<uint8_t> GetSpriteTileData(SpriteTile& sprite);
		void DeleteFrameBuffer(GLuint fbo);
		std::vector<unsigned char> LoadTexture(std::filesystem::path& path);
		void SetupSpriteTexture();
		void CreateSpriteTexture(Dimensions2& dimensions, std::vector<uint8_t>& data);
		SpriteSheetInfo ParseJson(std::filesystem::path& infoPath);
};
