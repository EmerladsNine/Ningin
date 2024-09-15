#pragma once
#include <filesystem>
#include <vector>
#include <string>

using namespace std;

class FileReader
{
	public:
		static vector<uint8_t> ReadFileBytes(const string& path);
		static vector<uint8_t> ReadFileBytes(const filesystem::path& path);
};
