#pragma once

#include "GL/glew.h"
#include "freetype/freetype.h"
#include "resource_manager/resource_manager.h"
#include "system/scenes_loader.h"
#include "system/window.h"
#include "system/window_options.h"
#include <glm.hpp>
#include <string>
#include <vector>

extern ResourceManager resourceManager;
extern glm::mat4 projectionMatrix;

extern const int ARRAY_LIMIT;
extern const int ATLAS_LIMIT;

class Game
{
public:
	static std::vector<Window> openedWindows;
	static SceneLoader sceneLoader;
	static void Init(std::string gameName, WindowOptions windowOptions, Dimensions2* dimensions,
		std::vector<std::string> scenes);
	static std::size_t new_window(std::string windowName, WindowOptions windowOptions, std::uint16_t sceneId,
		Dimensions2* dimensions);

private:
	FT_Library init_freetype();
	static void init_gl2d(Dimensions2* dimensions);
	static void init_resource_manager();
	static void main_loop();
};
