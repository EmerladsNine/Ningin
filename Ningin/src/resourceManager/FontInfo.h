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
		FontInfo(FT_Library& ftLibrary, filesystem::path fontPath, string name);

		static vector<FontInfo> GenerateInfoFromFolder(filesystem::path& path,
			FT_Library& ftLibrary);

		FT_Library& GetFtLibrary();
		filesystem::path& GetFontPath();
		string& GetName();

	private:
		FT_Library _ftLibrary;
		filesystem::path _fontPath;
		string _name;
};
