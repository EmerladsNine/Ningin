#include "FontInfo.h"
#include <filesystem>
#include <iostream>
#include <stdexcept>

using namespace std;

FontInfo::FontInfo(FT_Library& ftLibrary, filesystem::path& fontPath, string& name)
	: ftLibrary(ftLibrary), fontPath(fontPath), name(name) {}

vector<FontInfo> FontInfo::GenerateInfoFromFolder(filesystem::path& path, FT_Library& ftLibrary)
{
	vector<FontInfo> fonts_info_vec;
	try {
		for (auto& entry : filesystem::directory_iterator(path)) {
			if (entry.is_regular_file()) {
				string extension = entry.path().extension().string();
				if (extension == ".ttf" || extension == ".TTF") {
					string file_name = entry.path().filename().string();
					fonts_info_vec.emplace_back(ftLibrary, entry.path(), file_name);
				}
			}
		}
	}

	catch (filesystem::filesystem_error& e) {
		cerr << "Filesystem error: " << e.what() << endl;
		// Handle the error as needed
	}
	catch (exception& e) {
		cerr << "Exception: " << e.what() << endl;
		// Handle the error as needed
	}

	return fonts_info_vec;
}

FT_Library& FontInfo::GetFtLibrary()
{
	return ftLibrary;
}

filesystem::path& FontInfo::GetFontPath()
{
	return fontPath;
}

string& FontInfo::GetName()
{
	return name;
}
