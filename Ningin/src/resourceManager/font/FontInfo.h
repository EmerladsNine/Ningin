#pragma once

#include <freetype/freetype.h>
#include <filesystem>
#include <ft2build.h>
#include <string>
#include <vector>

using namespace std;

class FontInfo
{
	public:
		FontInfo(const filesystem::path fontPath, string name);

		static vector<FontInfo> GenerateInfoFromFolder(const filesystem::path& path);

		const filesystem::path& GetFontPath();
		string& GetName();

	private:
		filesystem::path _fontPath;
		string _name;
};
