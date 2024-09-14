#pragma once

#include "GL/glew.h"
#include "freetype/freetype.h"
#include "resourceManager/ResourceManager.h"
#include "system/SceneLoader.h"
#include "system/window.h"
#include "system/WindowOptions.h"
#include "scripting/ninginMono/MonoPaths.h"
#include <glm.hpp>
#include <string>
#include <vector>

using namespace std;

extern ResourceManager resourceManager;
extern glm::mat4 projectionMatrix;

extern const int ARRAY_LIMIT;
extern const int ATLAS_LIMIT;

class Game
{
	public:
		static vector<Window> openedWindows;
		static SceneLoader sceneLoader;

		static void Init(string gameName, WindowOptions windowOptions, Dimensions2* dimensions,
			vector<string> scenes, optional<MonoPaths> monoPath);

		static size_t new_window(string windowName, WindowOptions windowOptions,
			uint16_t sceneId, Dimensions2* dimensions);

	private:
		static void init_gl2d(Dimensions2* dimensions);
		static void init_resource_manager();
		FT_Library init_freetype();
		static void main_loop();
};
