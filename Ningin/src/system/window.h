#pragma once

#include "../math/Dimensions2.h"
#include "../sceneSystem/Scene.h"
#include "SceneManager.h"
#include <GLFW/glfw3.h>
#include <string>

class Window
{
	public:
		GLFWwindow* _win;
		SceneManager sceneManager;
		Dimensions2* dimensions;

		Window(std::string title, bool isFullscreen, Scene scene, Dimensions2* dimensions);

	private:
		void InitOpenGL(GLFWwindow* window);
		void InitGlfw();

		GLFWwindow* StartWindow(std::string title, bool isFullscreen, Dimensions2* dimensions);
};
