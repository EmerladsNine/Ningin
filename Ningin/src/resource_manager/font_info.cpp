#include "font_info.h"
#include <filesystem>
#include <iostream>
#include <stdexcept>

FontInfo::FontInfo(const FT_Library& ft_library, const std::filesystem::path& font_path, const std::string& name)
	: ft_library(ft_library), font_path(font_path), name(name)
{
}

// Static method to generate FontInfo instances from a folder
std::vector<FontInfo> FontInfo::generateInfoFromFolder(const std::filesystem::path& path, const FT_Library& ft_library)
{
	std::vector<FontInfo> fonts_info_vec;

	try
	{
		for (const auto& entry : std::filesystem::directory_iterator(path))
		{
			if (entry.is_regular_file())
			{
				std::string extension = entry.path().extension().string();
				if (extension == ".ttf" || extension == ".TTF")
				{
					std::string file_name = entry.path().filename().string();
					fonts_info_vec.emplace_back(ft_library, entry.path(), file_name);
				}
			}
		}
	}
	catch (const std::filesystem::filesystem_error& e)
	{
		std::cerr << "Filesystem error: " << e.what() << std::endl;
		// Handle the error as needed
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		// Handle the error as needed
	}

	return fonts_info_vec;
}

// Accessors
const FT_Library& FontInfo::getFtLibrary() const
{
	return ft_library;
}

const std::filesystem::path& FontInfo::getFontPath() const
{
	return font_path;
}

const std::string& FontInfo::getName() const
{
	return name;
}