#include "window.h"
#include <GLFW/glfw3.h>

static void callback_function(GLFWwindow* window, int width, int height)
{
	//TODO
}

Window::Window(std::string title, bool is_fullscreen, Scene scene, Dimensions2* dimensions) : sceneManager(SceneManager(scene)), dimensions(dimensions)
{
	InitGlfw();
	GLFWwindow* window = StartWindow(title, is_fullscreen, dimensions);
	InitOpenGL(window);
	glfwSetFramebufferSizeCallback(window, callback_function);
	_win = window;
}

void Window::InitGlfw()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* Window::StartWindow(std::string title, bool is_fullscreen, Dimensions2* dimensions)
{
	if (is_fullscreen) {
		GLFWwindow* window = glfwCreateWindow(dimensions->width, dimensions->height, title.c_str(), glfwGetPrimaryMonitor(), NULL);
		glfwMakeContextCurrent(window);
		return window;
	}
	else {
		GLFWwindow* window = glfwCreateWindow(dimensions->width, dimensions->height, title.c_str(), NULL, NULL);
		glfwMakeContextCurrent(window);
		return window;
	}
}

void Window::InitOpenGL(GLFWwindow* window)
{
	//TODO INIT OPENGL JAWAD
}