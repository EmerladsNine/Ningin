#pragma once

#include <string>
#include <filesystem>

using namespace std;

class Enironment
{
	public:
		static filesystem::path GetGameDirectory();
};
