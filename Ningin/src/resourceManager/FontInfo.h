#pragma once

#include <freetype/freetype.h>
#include <filesystem>
#include <ft2build.h>
#include <string>
#include <vector>

class FontInfo
{
	public:
		FontInfo(FT_Library& ftLibrary, std::filesystem::path& fontPath, std::string& name);

		static std::vector<FontInfo> GenerateInfoFromFolder(std::filesystem::path& path,
			FT_Library& ftLibrary);

		FT_Library& GetFtLibrary();
		std::filesystem::path& GetFontPath();
		std::string& GetName();

	private:
		FT_Library ftLibrary;
		std::filesystem::path fontPath;
		std::string name;
};
