#include "Ningin.h"
#include "sceneSystem/World.h"
#include "scripting/ScriptingEngine.h"
#include "utills/Timer.h"
#include <thread>
#include <chrono>


using Clock = chrono::high_resolution_clock;
using TimePoint = chrono::time_point<Clock>;

ResourceManager resourceManager = ResourceManager();
glm::mat4 projectionMatrix = glm::mat4(1.0f);

vector<Window> Game::openedWindows;
SceneLoader Game::sceneLoader;

const int ARRAY_LIMIT = 100;
const int ATLAS_LIMIT = 256;

void Game::Init(string gameName, WindowOptions windowOptions, Dimensions2* dimensions,
	vector<string> scenes, optional<MonoPaths> monoPath)
{
	//Create new window with no scene
	NewWindow(gameName, windowOptions, -1, dimensions);

	InitGl2d(dimensions);
	InitResourceManager();
	World::InitDefaultComponentSystem();
	ScriptingEngine::Init(monoPath);
	
	for (auto& scene : scenes)
	{
		sceneLoader.LoadSceneFromFile(scene);
	}
	
	//Initialise first window scene manager
	openedWindows[0].sceneManager = SceneManager(sceneLoader.GetSceneFromId(0));
}

void Game::Start()
{
	Game::MainLoop();
}

size_t Game::NewWindow(string windowName, WindowOptions windowOptions, uint16_t sceneId,
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

FT_Library Game::InitFreetype()
{
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) // all functions return a value different than 0 whenever an error occurred
		throw runtime_error("ERROR::FREETYPE: Could not init FreeType Library");
	return ft;
}

void Game::InitGl2d(Dimensions2* dimensions)
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

void Game::InitResourceManager()
{
	// TODO
}

void Game::MainLoop()
{
	Timer timer;
	while (true)
	{
		//This Should Be Removed Later ... Makes Frames Slower
		std::this_thread::sleep_for(std::chrono::milliseconds(10));


		glfwPollEvents();
		glClearColor(0, 100/255.0f, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		vector<size_t> windowIndicesToDelete;

		size_t index = 0;

		for (auto& win : openedWindows)
		{
			
			if (!glfwWindowShouldClose(win.glfwWin)) win.sceneManager.NewFrame(timer);
			else windowIndicesToDelete.push_back(index);
			
			glfwSwapBuffers(win.glfwWin);

			index++;
		}

		sort(windowIndicesToDelete.rbegin(), windowIndicesToDelete.rend());

		// Remove elements in descending order to avoid invalidating indices
		for (size_t index : windowIndicesToDelete) {
			openedWindows.erase(openedWindows.begin() + index);
		}

		if (openedWindows.size() == 0)
			break;

		timer.ResetDeltaTime();
	}
}

int main()
{
	Game::Init("Example", WindowOptions::Windowed, new Dimensions2(500, 500), { "Scene" },
		MonoPaths("mono/lib","example.dll"));
	Game::Start();
	return 0;
}
