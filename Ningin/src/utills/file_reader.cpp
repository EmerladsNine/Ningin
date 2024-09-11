#include "file_reader.h"
#include <fstream>

std::vector<uint8_t> FileReader::ReadFileBytes(const std::string& path)
{
	std::ifstream file(path,
		std::ios::binary // Ensures that the file's content is read or written in binary format
		|
		std::ios::ate // Immediately positions the file pointer at the end of the file after opening
	);

	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open file: " + path);
	}

	// Get file size by getting the position at the end of file.
	std::ifstream::pos_type fileSize = file.tellg();

	// Position the file pointer to the beginning of the file.
	file.seekg(0,            // Offset
		std::ios::beg // Offset is relative to the begining of the file.
	);

	// Read file contents into byte vector.
	std::vector<uint8_t> buffer(fileSize);
	if (!file.read(reinterpret_cast<char*>(buffer.data()), fileSize))
	{
		throw std::runtime_error("Failed to read file: " + path);
	}

	return buffer;
}