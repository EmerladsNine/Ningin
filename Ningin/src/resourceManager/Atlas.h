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

using namespace std;

class Atlas
{
	public:
		Atlas(size_t id);

		void GenerateAtlas();

		void AddSprite(const filesystem::path& path, string& name);
		void AddSpritesWithJson(filesystem::path& spriteSheetPath, filesystem::path& infoPath);
		void AddSprites(filesystem::path& spriteSheetPath, SpriteSheetInfo& info);
		
		bool CanAddSprite();
		bool CanAddSpriteSheet(SpriteSheetInfo& spriteSheet);

		void Unbind();
		void Bind();

	private:
		unordered_map<string, Sprite> _sprites;
		GLuint _atlasID;
		size_t _id;

		int _index;

		void AddSpriteFromData(vector<uint8_t>& data, Dimensions2& dimensions, string& name);
		GLuint GenerateFrameBuffer(GLuint texture);
		vector<uint8_t> GetSpriteTileData(SpriteTile& sprite);
		void DeleteFrameBuffer(GLuint fbo);
		vector<unsigned char> LoadTexture(const filesystem::path& path);
		void SetupSpriteTexture();
		void CreateSpriteTexture(Dimensions2& dimensions, vector<uint8_t>& data);
		SpriteSheetInfo ParseJson(filesystem::path& infoPath);
};
