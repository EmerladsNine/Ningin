#include "Ningin.h"
#include "sceneSystem/World.h"
#include "scripting/ScriptingEngine.h"

ResourceManager resourceManager = ResourceManager();
glm::mat4 projectionMatrix = glm::mat4(1.0f);

std::vector<Window> Game::openedWindows;
SceneLoader Game::sceneLoader;

const int ARRAY_LIMIT = 100;
const int ATLAS_LIMIT = 256;

void Game::Init(std::string gameName, WindowOptions windowOptions, Dimensions2* dimensions,
	std::vector<std::string> scenes, std::optional<MonoPaths> monoPath)
{
	//Create new window with no scene
	new_window(gameName, windowOptions, -1, dimensions);

	init_gl2d(dimensions);
	init_resource_manager();
	World::InitDefaultComponentSystem();
	ScriptingEngine::Init(monoPath);
	
	for (auto& scene : scenes)
	{
		sceneLoader.LoadSceneFromFile(scene);
	}
	
	//Initialise first window scene manager
	openedWindows[0].sceneManager = SceneManager(sceneLoader.GetSceneFromId(0));
}

std::size_t Game::new_window(std::string windowName, WindowOptions windowOptions, uint16_t sceneId,
	Dimensions2* dimensions)
{
	switch (windowOptions)
	{
		case NoWindow: break;

		case FullScreen:
			openedWindows.push_back(Window(windowName, true, sceneLoader.GetSceneFromId(sceneId),
				dimensions));
			break;

		case Windowed:
			openedWindows.push_back(Window(windowName, false, sceneLoader.GetSceneFromId(sceneId),
				dimensions));
			break;

		default: break;
	}

	return openedWindows.size() - 1;
}

FT_Library Game::init_freetype()
{
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) // all functions return a value different than 0 whenever an error occurred
		throw std::runtime_error("ERROR::FREETYPE: Could not init FreeType Library");
	return ft;
}

void Game::init_gl2d(Dimensions2* dimensions)
{
	glViewport(0, 0, dimensions->width, dimensions->height);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);
	glDepthFunc(GL_LEQUAL);
}

void Game::init_resource_manager()
{
	// TODO
}

void Game::main_loop()
{
	while (true)
	{
		for (auto& win : openedWindows)
		{
			win.sceneManager.NewFrame(0);
		}
	}
}

int main()
{
	Game::Init("ma khasak", WindowOptions::Windowed, new Dimensions2(100, 100), { "Scene" }, MonoPaths("mono/lib","example.dll"));
	return 0;
}
