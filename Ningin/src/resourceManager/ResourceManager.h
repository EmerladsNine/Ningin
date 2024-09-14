#pragma once

#include "Atlas.h"
#include "Font.h"
#include "FontInfo.h"
#include "Shader.h"
#include "ShaderInfo.h"
#include "spriteInfo.h"
#include "Texture2D.h"
#include "TextureInfo.h"
#include <filesystem>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
//#include "../physics_manager/physics_material2d.h"

class ResourceManager
{
	public:
		ResourceManager() = default;

		void AddSprite(SpriteInfo& info);
		void LoadSprites(std::vector<SpriteInfo>& info);
		void LoadSpriteSheet();

		void LoadShader(ShaderInfo& info);
		void LoadShaders(std::vector<ShaderInfo>& info);

		Shader GetShader(std::string& name);

		void LoadTexture(TextureInfo& info);
		void LoadTextures(std::vector<TextureInfo>& info);

		Texture2D GetTexture(std::string& name);

		void LoadFont(FontInfo& info);
		void LoadFonts(std::vector<FontInfo>& info);
		void LoadFontsFromFolder(std::filesystem::path& path, FT_Library ftLibrary);

		Font GetFont(std::string& name);

	private:
		std::unordered_map<std::string, Texture2D> _textures;
		std::unordered_map<std::string, SpriteInfo> _sprites;
		std::unordered_map<std::string, Shader> _shaders;
		std::unordered_map<std::string, Font> _fonts;
		std::vector<Atlas> _atlases;

		//std::unordered_map<std::string, PhyscicsMaterial2D> physicsMaterials2D;
};
