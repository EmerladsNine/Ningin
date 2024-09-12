#include "ResourceManager.h"
#include <fstream>
#include <json/json.h>

void ResourceManager::AddSprite(SpriteInfo& info)
{
	if (atlases.empty() || !atlases.back().CanAddSprite())
	{
		atlases.emplace_back(atlases.size());
	}

	Atlas& atlas = atlases.back();
	std::filesystem::path path = info.GetPath();
	std::string name = info.GetName();
	atlas.AddSprite(path, name);

	SpriteInfo spriteInfo = info;
	spriteInfo.SetAtlasId(atlases.size() - 1);

	sprites[spriteInfo.GetName()] = spriteInfo;
}

void ResourceManager::LoadSprites(std::vector<SpriteInfo>& info)
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
	shaders.insert(std::make_pair(info.GetName(), shader));
}

void ResourceManager::LoadShaders(std::vector<ShaderInfo>& info)
{
	for (auto& shaderInfo : info)
	{
		LoadShader(shaderInfo);
	}
}

Shader ResourceManager::GetShader(std::string& name)
{
	auto it = shaders.find(name);
	if (it != shaders.end())
	{
		return it->second;
	}
	throw std::runtime_error("Shader not found");
}

void ResourceManager::LoadTexture(TextureInfo& info)
{
	Texture2D texture(info.GetImgPath(), info.HasAlpha());
	textures.insert(std::make_pair(info.GetName(), texture));
}

void ResourceManager::LoadTextures(std::vector<TextureInfo>& info)
{
	for (auto& textureInfo : info)
	{
		LoadTexture(textureInfo);
	}
}

Texture2D ResourceManager::GetTexture(std::string& name)
{
	auto it = textures.find(name);
	if (it != textures.end())
	{
		return it->second;
	}
	throw std::runtime_error("Texture not found");
}

void ResourceManager::LoadFont(FontInfo& info)
{
	Font font(info.GetFontPath(), info.GetFtLibrary());
	fonts.insert(std::make_pair(info.GetName(), font));
}

void ResourceManager::LoadFonts(std::vector<FontInfo>& info)
{
	for (auto& fontInfo : info)
	{
		LoadFont(fontInfo);
	}
}

void ResourceManager::LoadFontsFromFolder(std::filesystem::path& path, FT_Library ftLibrary)
{
	std::vector<FontInfo> fontInfos = FontInfo::GenerateInfoFromFolder(path, ftLibrary);
	for (auto& fontInfo : fontInfos)
	{
		LoadFont(fontInfo);
	}
}

Font ResourceManager::GetFont(std::string& name)
{
	auto it = fonts.find(name);
	if (it != fonts.end())
	{
		return it->second;
	}
	throw std::runtime_error("Font not found");
}