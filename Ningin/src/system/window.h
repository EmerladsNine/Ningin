#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include "scene_manager.h"
#include "../scene_system/scene.h"
#include "../math/dimensions2.h"

class Window
{
public:
	GLFWwindow* _win;
	SceneManager sceneManager;
	Dimensions2* dimensions;
	Window(std::string title, bool is_fullscreen , Scene scene , Dimensions2* dimensions);
private:
	void InitGlfw();
	GLFWwindow* StartWindow(std::string title, bool is_fullscreen, Dimensions2* dimensions);
	void InitOpenGL(GLFWwindow* window);
};