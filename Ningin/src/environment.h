#pragma once
#include <filesystem>

class Environment
{
	public:
		static std::filesystem::path GetGameDirectory();
};
