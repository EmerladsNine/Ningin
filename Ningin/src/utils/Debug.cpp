#include "Debug.h"
#include <iostream>

void LogInfo(const string& message)
{
	cerr << "[Info] " << message << endl;
}

void LogError(const string& message)
{
	cerr << "[Error] " << message << endl;
}

void LogWarning(const string& message)
{
	cerr << "[Warning] " << message << endl;
}
