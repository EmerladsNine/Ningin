#pragma once

#include <vector>
#include <string>

using namespace std;

class FileReader
{
	public:
		static vector<uint8_t> ReadFileBytes(const string& path);
};
