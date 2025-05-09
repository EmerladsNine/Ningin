#pragma once

#define GLFW_INCLUDE_VULKAN

#include "../math/Dimensions2.h"
#include "../sceneSystem/Scene.h"
#include "SceneManager.h"
#include <GL/glew.h>
#include <glm.hpp>
#include <GLFW/glfw3.h>
#include <string>
#include "RenderingApi.h"
#include "QueueFamilyIndices.h"

using namespace std;

namespace Ningin
{
	class Window
	{
	public:
		GLFWwindow* glfwWin;
		VkInstance* vkInstance;

		Dimensions2* dimensions;

		Window(string title, bool isFullscreen, Dimensions2* dimensions, RenderingApi renderingApi);

		VkDebugUtilsMessengerEXT getDebugMessenger();
		VkSurfaceKHR getSurface();
		VkDevice getDevice();

	private:
		VkDebugUtilsMessengerEXT debugMessenger;

		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		VkSurfaceKHR surface;

		VkDevice device;

		VkQueue graphicsQueue;
		VkQueue presentQueue;

		void InitOpenGL(GLFWwindow* window);
		void InitGlfw();
		void initVulkan(string title);

		void createVkInstance(string title);

		void createSurface();

		GLFWwindow* StartWindow(string title, bool isFullscreen, Dimensions2* dimensions);

		void setupDebugMessenger();

		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		std::vector<const char*> getRequiredExtensions();
		bool checkValidationLayerSupport();

		bool isDeviceSuitable(VkPhysicalDevice device);
		void pickPhysicalDevice();

		void createLogicalDevice();
	};

	void setProjection(Dimensions2* dimensions);

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT
		messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
		const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator,
		VkDebugUtilsMessengerEXT* pDebugMessenger);

	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
		const VkAllocationCallbacks* pAllocator);

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
}
