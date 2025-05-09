#include "Debug.h"
#include <iostream>

const string RESET = "\033[0m";
const string BLACK = "\033[30m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";

void SetConsoleColor(const std::string& color) {
	std::cerr << color;
}

void LogInfo(const string& message)
{
	SetConsoleColor(CYAN);
	cerr << "[Info] " << message << endl;
	SetConsoleColor(WHITE);
}

void LogError(const string& message)
{
	SetConsoleColor(RED);
	cerr << "[Error] " << message << endl;
	SetConsoleColor(WHITE);
}

void LogWarning(const string& message)
{
	SetConsoleColor(YELLOW);
	cerr << "[Warning] " << message << endl;
	SetConsoleColor(WHITE);
}
