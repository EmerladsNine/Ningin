#include "ResourceManager.h"
#include <fstream>
#include <json/json.h>

void ResourceManager::AddSprite(SpriteInfo& info)
{
	if (_atlases.empty() || !_atlases.back().CanAddSprite())
	{
		_atlases.emplace_back(_atlases.size());
	}

	Atlas& atlas = _atlases.back();
	//auto path = info.GetPath();
	string name = info.GetName();
	atlas.AddSprite(info.GetPath(), name);

	SpriteInfo spriteInfo = info;
	spriteInfo.SetAtlasId(_atlases.size() - 1);

	_sprites[spriteInfo.GetName()] = spriteInfo;
}

void ResourceManager::LoadSprites(vector<SpriteInfo>& info)
{
	for (auto& spriteInfo : info)
	{
		AddSprite(spriteInfo);
	}
}

void ResourceManager::LoadSpriteSheet()
{
	// TODO: Implement Loading sprite sheet functionality
}

void ResourceManager::LoadShader(ShaderInfo& info)
{
	Shader shader(info.GetPath("vertex"), info.GetPath("fragment"));
	_shaders.insert(make_pair(info.GetName(), shader));
}

void ResourceManager::LoadShaders(vector<ShaderInfo>& info)
{
	for (auto& shaderInfo : info)
	{
		LoadShader(shaderInfo);
	}
}

Shader ResourceManager::GetShader(const string& name)
{
	auto it = _shaders.find(name);
	if (it != _shaders.end())
	{
		return it->second;
	}

	throw runtime_error("Shader not found");
}

void ResourceManager::LoadTexture(TextureInfo& info)
{
	Texture2D texture(info.GetImgPath(), info.HasAlpha());
	_textures.insert(make_pair(info.GetName(), texture));
}

void ResourceManager::LoadTextures(vector<TextureInfo>& info)
{
	for (auto& textureInfo : info)
	{
		LoadTexture(textureInfo);
	}
}

Texture2D ResourceManager::GetTexture(const string& name)
{
	auto it = _textures.find(name);
	if (it != _textures.end())
	{
		return it->second;
	}

	throw runtime_error("Texture not found");
}

void ResourceManager::LoadFont(FontInfo& info)
{
	Font font(info.GetFontPath());
	_fonts.insert(make_pair(info.GetName(), font));
}

void ResourceManager::LoadFonts(vector<FontInfo>& info)
{
	for (auto& fontInfo : info)
	{
		LoadFont(fontInfo);
	}
}

void ResourceManager::LoadFontsFromFolder(const filesystem::path& path)
{
	vector<FontInfo> fontInfos = FontInfo::GenerateInfoFromFolder(path);
	for (auto& fontInfo : fontInfos)
	{
		LoadFont(fontInfo);
	}
}

Font ResourceManager::GetFont(const string& name)
{
	auto it = _fonts.find(name);
	if (it != _fonts.end())
	{
		return it->second;
	}

	throw runtime_error("Font not found");
}
