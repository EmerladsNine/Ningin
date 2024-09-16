#pragma once

#include <filesystem>
#include <string>

using namespace std;

class SpriteInfo
{
	public:
		SpriteInfo(string& name, const filesystem::path& path);
		SpriteInfo() = default;

		void SetAtlasId(size_t atlasId);

		const filesystem::path GetPath();
		size_t GetAtlasId();
		string GetName();

	private:
		filesystem::path _path;
		size_t _atlasId;
		string _name;
};
