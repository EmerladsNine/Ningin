#include "window.h"
#include <glm.hpp>
#include "../ningin.h"

static void callback_function(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);

	projectionMatrix = glm::ortho(0.0f, static_cast<float>(width),
		static_cast<float>(height), 0.0f, -1.0f, 1.0f);
}

Window::Window(string title, bool isFullscreen, Scene* scene, Dimensions2* dimensions)
	: sceneManager(SceneManager(scene)), dimensions(dimensions)
{
	InitGlfw();
	GLFWwindow* window = StartWindow(title, isFullscreen, dimensions);

	projectionMatrix = glm::ortho(0.0f, static_cast<float>(dimensions->width), 
		static_cast<float>(dimensions->height), 0.0f, -1.0f, 1.0f);

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
	if (isFullscreen)
	{
		GLFWwindow* window = glfwCreateWindow(static_cast<int>(dimensions->width)
			, static_cast<int>(dimensions->height), title.c_str(), glfwGetPrimaryMonitor(), NULL);

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
