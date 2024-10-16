#pragma once
#include "GLFW/glfw3.h"
#include "unordered_map"
class KeyInput
{
public:
	static std::unordered_map<int, bool> keys;
	static void SetupKeyInputs(GLFWwindow* window);
private:
	static void SetIsKeyDown(int key, bool isDown);
	static void Callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

bool IsKeyDown(int key);