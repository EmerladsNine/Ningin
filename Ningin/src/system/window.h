#pragma once

#include "../math/Dimensions2.h"
#include "../sceneSystem/Scene.h"
#include "SceneManager.h"
#include <GLFW/glfw3.h>
#include <string>

using namespace std;

class Window
{
	public:
		GLFWwindow* win;
		SceneManager sceneManager;
		Dimensions2* dimensions;

		Window(string title, bool isFullscreen, Scene* scene, Dimensions2* dimensions);

	private:
		void InitOpenGL(GLFWwindow* window);
		void InitGlfw();

		GLFWwindow* StartWindow(string title, bool isFullscreen, Dimensions2* dimensions);
};
