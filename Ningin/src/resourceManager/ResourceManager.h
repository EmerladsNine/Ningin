#pragma once

#include "atlas/Atlas.h"
#include "font/Font.h"
#include "font/FontInfo.h"
#include "shader/Shader.h"
#include "shader/ShaderInfo.h"
#include "atlas/spriteInfo.h"
#include "texture/Texture2D.h"
#include "texture/TextureInfo.h"
#include <filesystem>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
//#include "../physics_manager/physics_material2d.h"

using namespace std;

class ResourceManager
{
	public:
		ResourceManager() = default;

		void AddSprite(SpriteInfo& info);
		void LoadSprites(vector<SpriteInfo>& info);
		void LoadSpriteSheet();

		void LoadShader(ShaderInfo& info);
		void LoadShaders(vector<ShaderInfo>& info);

		Shader GetShader(const string& name);

		void LoadTexture(TextureInfo& info);
		void LoadTextures(vector<TextureInfo>& info);

		Texture2D GetTexture(const string& name);

		void LoadFont(FontInfo& info);
		void LoadFonts(vector<FontInfo>& info);
		void LoadFontsFromFolder(const filesystem::path& path);

		Font GetFont(const string& name);

	private:
		unordered_map<string, Texture2D> _textures;
		unordered_map<string, SpriteInfo> _sprites;
		unordered_map<string, Shader> _shaders;
		unordered_map<string, Font> _fonts;
		vector<Atlas> _atlases;

		//unordered_map<string, PhyscicsMaterial2D> physicsMaterials2D;
};
