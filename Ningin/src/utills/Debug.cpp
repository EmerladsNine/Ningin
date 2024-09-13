#include "Debug.h"
#include <iostream>

void LogInfo(const std::string& message)
{
	std::cerr << "[Info] " << message << std::endl;
}

void LogError(const std::string& message)
{
	std::cerr << "[Error] " << message << std::endl;
}

void LogWarning(const std::string& message)
{
	std::cerr << "[Warning] " << message << std::endl;
}
