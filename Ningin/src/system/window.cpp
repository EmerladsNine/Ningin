#include "window.h"
#include <glm.hpp>
#include "../ningin.h"
#include <iostream>

namespace Ningin
{
	void setProjection(Dimensions2* dimensions)
	{
		projectionMatrix = glm::ortho(0.0f, static_cast<float>(dimensions->width),
			static_cast<float>(dimensions->height), 0.0f, -1.0f, 1.0f);
		projectionUBO.SetUBOFloatPtr(sizeof(glm::mat4), 0, glm::value_ptr(projectionMatrix));
	}

	static void callback_function(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);

		windowDimensions = Dimensions2(width, height);

		setProjection(&windowDimensions);
	}

	Window::Window(string title, bool isFullscreen, Dimensions2* dimensions)
		:  dimensions(dimensions)
	{
		InitGlfw();
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

		if (isFullscreen)
		{
			*dimensions = Dimensions2(mode->width, mode->height);
		}

		GLFWwindow* window = StartWindow(title, isFullscreen, dimensions);

		windowDimensions = *dimensions;

		InitOpenGL(window);
		glfwSetFramebufferSizeCallback(window, callback_function);
		glfwWin = window;
	}

	void Window::InitGlfw()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	GLFWwindow* Window::StartWindow(string title, bool isFullscreen, Dimensions2* dimensions)
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		if (isFullscreen)
		{
			GLFWwindow* window = glfwCreateWindow(static_cast<int>(dimensions->width)
				, static_cast<int>(dimensions->height), title.c_str(), monitor, NULL);

			glfwMakeContextCurrent(window);
			return window;
		}
		else
		{
			GLFWwindow* window = glfwCreateWindow(static_cast<int>(dimensions->width)
				, static_cast<int>(dimensions->height), title.c_str(), NULL, NULL);

			glfwMakeContextCurrent(window);
			return window;
		}
	}

	void Window::InitOpenGL(GLFWwindow* window)
	{
		GLenum err = glewInit();
		if (err != GLEW_OK) {
			ostringstream oss;
			oss << "Failed to initialize GLEW:\n" << glewGetErrorString(err) << "\n";
			throw runtime_error(oss.str());
		}
	}
}