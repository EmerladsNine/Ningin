#pragma once

#include <filesystem>
#include <string>

class SpriteInfo
{
	public:
		SpriteInfo(std::string& name, std::filesystem::path& path);
		SpriteInfo() = default;

		void SetAtlasId(std::size_t atlasId);

		std::filesystem::path GetPath();
		std::size_t GetAtlasId();
		std::string GetName();

	private:
		std::filesystem::path path;
		std::size_t atlasId;
		std::string name;
};
