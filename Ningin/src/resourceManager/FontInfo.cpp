#include "FontInfo.h"
#include <filesystem>
#include <iostream>
#include <stdexcept>

FontInfo::FontInfo(const filesystem::path fontPath, string name) : _fontPath(fontPath), _name(name) {}

vector<FontInfo> FontInfo::GenerateInfoFromFolder(const filesystem::path& path)
{
	vector<FontInfo> fonts_info_vec;
	try
	{
		for (auto& entry : filesystem::directory_iterator(path))
		{
			if (entry.is_regular_file())
			{
				string extension = entry.path().extension().string();
				if (extension == ".ttf" || extension == ".TTF")
				{
					string file_name = entry.path().filename().string();
					filesystem::path path = entry.path();
					fonts_info_vec.push_back(FontInfo(path, file_name));
				}
			}
		}
	}

	catch (filesystem::filesystem_error& e)
	{
		cerr << "Filesystem error: " << e.what() << endl;
		// Handle the error as needed
	}
	catch (exception& e)
	{
		cerr << "Exception: " << e.what() << endl;
		// Handle the error as needed
	}

	return fonts_info_vec;
}

const filesystem::path& FontInfo::GetFontPath()
{
	return _fontPath;
}

string& FontInfo::GetName()
{
	return _name;
}
