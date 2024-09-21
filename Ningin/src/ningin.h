#pragma once

#include <GL/glew.h>
#include "freetype/freetype.h"
#include "resourceManager/ResourceManager.h"
#include "system/SceneLoader.h"
#include "system/window.h"
#include "system/WindowOptions.h"
#include "scripting/ninginMono/MonoPaths.h"
#include "resourceManager/opengl/ubo.h"
#include "math/Range.h"
#include "Environment.h"
#include <glm.hpp>
#include <string>
#include <vector>

using namespace std;

extern ResourceManager resourceManager;
extern glm::mat4 projectionMatrix;
extern Dimensions2 windowDimensions;
extern FT_Library ftLibrary;

extern UBO projectionUBO;

extern const int ARRAY_LIMIT;
extern const int ATLAS_LIMIT;

extern const Range AnimationTimeRange;
extern const Range colorRange;

class Game
{
	public:
		static vector<Window> openedWindows;
		static SceneLoader sceneLoader;

		static void Init(string gameName, WindowOptions windowOptions, Dimensions2* dimensions,
			vector<string> scenes, optional<MonoPaths> monoPath, bool debugMode);
		static void Start();
		static size_t NewWindow(string windowName, WindowOptions windowOptions,
			uint16_t sceneId, Dimensions2* dimensions);

	private:
		static void InitGl2d(Dimensions2* dimensions);
		static void InitResourceManager();
		static void InitFreetype();
		static void SetUBO(Dimensions2* dimensions);
		static void MainLoop();
};
