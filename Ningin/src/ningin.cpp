#include "Ningin.h"
#include "sceneSystem/World.h"
#include "scripting/ScriptingEngine.h"
#include "utils/Timer.h"
#include <filesystem>

ResourceManager resourceManager = ResourceManager();
glm::mat4 projectionMatrix = glm::mat4(1.0f);
Dimensions2 windowDimensions(100, 100);
FT_Library ftLibrary;

UBO projectionUBO = UBO();

const int ARRAY_LIMIT = 100;
const int ATLAS_LIMIT = 256;

const Range AnimationTimeRange(0.05, 20);
const Range colorRange(0, 255);

vector<Window> Game::openedWindows;
SceneLoader Game::sceneLoader;

void Game::Init(string gameName, WindowOptions windowOptions, Dimensions2* dimensions,
	vector<string> scenes, optional<MonoPaths> monoPath, bool debugMode)
{
	NewWindow(gameName, windowOptions, -1, dimensions); // Create new window with no scene

	InitFreetype();
	InitGl2d(dimensions);
	InitResourceManager();
	SetUBO(dimensions);

	World::InitDefaultComponentSystem();
	ScriptingEngine::Init(monoPath,debugMode);
	
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
	if (FT_Init_FreeType(&ftLibrary)) // all functions return a value != 0 whenever an error occurred
		throw runtime_error("ERROR::FREETYPE: Could not init FreeType Library");
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
	filesystem::path gameDirectory = Environment::GetGameDirectory();

	resourceManager.LoadFontsFromFolder(gameDirectory / "default\\fonts");

	ShaderInfo spriteShader(gameDirectory / "shaders\\sprite_vs.vs",
		gameDirectory / "shaders\\sprite_fs.frag", string("sprite"));

	ShaderInfo textShader(gameDirectory / "shaders\\text_vs.vs",
		gameDirectory / "shaders\\text_fs.frag", string("text"));

	resourceManager.LoadShader(spriteShader);
	resourceManager.LoadShader(textShader);

	TextureInfo texture(gameDirectory / "img.png", true, string("sprite"));

	resourceManager.LoadTexture(texture);
}

void Game::SetUBO(Dimensions2* dimensions)
{
	vector<Shader> shadersUniforms = { resourceManager.GetShader(string("sprite")),
		resourceManager.GetShader(string("text")) };

	projectionUBO = UBO(shadersUniforms, "Matrix", sizeof(glm::mat4));

	setProjection(dimensions);
}

void Game::MainLoop()
{
	Timer timer;

	while (true)
	{
		glfwPollEvents();
		glClearColor(0.3, 0.2, 0.5, 1.0f);
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
			glfwDestroyWindow(openedWindows[index].glfwWin);
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
		MonoPaths("mono/lib","example.dll"),false);
	Game::Start();
	return 0;
}
