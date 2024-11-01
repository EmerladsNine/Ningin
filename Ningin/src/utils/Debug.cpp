#include "Debug.h"
#include <iostream>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      // Black
#define RED     "\033[31m"      // Red
#define GREEN   "\033[32m"      // Green
#define YELLOW  "\033[33m"      // Yellow
#define BLUE    "\033[34m"      // Blue
#define MAGENTA "\033[35m"      // Magenta
#define CYAN    "\033[36m"      // Cyan
#define WHITE   "\033[37m"      // White

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
