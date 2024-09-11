#pragma once
#include <vector>
#include <string>

class FileReader
{
public:
	static std::vector<uint8_t> ReadFileBytes(const std::string& path);
};