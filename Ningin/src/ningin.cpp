#include "Ningin.h"
#include "scripting/ScriptingEngine.h"
#include "utils/Timer.h"
#include "input/KeyInput.h"
#include "utils/Debug.h"
#include <filesystem>
#include <portaudio.h>

namespace Ningin
{
	ResourceManager resourceManager = ResourceManager();
	glm::mat4 projectionMatrix = glm::mat4(1.0f);
	Dimensions2 windowDimensions(100, 100);
	FT_Library ftLibrary;

	RenderingApi renderingApi;

	UBO projectionUBO = UBO();

	int ARRAY_LIMIT;
	const int ATLAS_LIMIT = 256;

	const Range AnimationTimeRange(0.05f, 20.0f);
	const Range colorRange(0, 255);

	std::optional<Window> Game::openedWindow;
	SceneLoader Game::sceneLoader;

	void Game::Init(string gameName, WindowOptions windowOptions, Dimensions2* dimensions,
		vector<string> scenes, optional<MonoPaths> monoPath, bool debugMode, RenderingApi renderingApi)
	{
		NewWindow(gameName, windowOptions, -1, dimensions, renderingApi); // Create new window with no scene

		glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &ARRAY_LIMIT);

		InitFreetype();
		InitGl2d(dimensions);
		InitResourceManager();
		SetUBO(dimensions);

		ScriptingEngine::Init(monoPath,debugMode);

		for (auto& scene : scenes)
		{
			sceneLoader.LoadSceneFromFile(scene);
		}
	
		//Initialise first window scene manager
		if(openedWindow.has_value())
		{
			KeyInput::SetupKeyInputs(openedWindow.value().glfwWin);
			SceneManager::currentScene = sceneLoader.GetSceneFromId(0);
		}
	}

	void Game::Start()
	{
		Game::MainLoop();
	}

	void Game::NewWindow(string windowName, WindowOptions windowOptions, uint16_t sceneId,
		Dimensions2* dimensions, RenderingApi renderingApi)
	{
		switch (windowOptions)
		{
			case NoWindow: break;

			case FullScreen:
				openedWindow = Window(windowName, true,
					dimensions, renderingApi);
				break;

			case Windowed:
				openedWindow = Window(windowName, false,
					dimensions, renderingApi);
				break;

			default: break;
		}
	}

	void Game::InitFreetype()
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

		ShaderInfo spriteShader("sprite", gameDirectory / "shaders\\sprite_vs.vs",
			gameDirectory / "shaders\\sprite_fs.frag", nullptr);

		ShaderInfo textShader("text", gameDirectory / "shaders\\text_vs.vs",
			gameDirectory / "shaders\\text_fs.frag", nullptr);

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
		int statistics_count = 0;
		float result = 0;
		Timer timer;

		while (true) // statistics_count < 1000
		{
			statistics_count++;
			glfwPollEvents();
			glClearColor(0.3f, 0.2f, 0.5f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			float deltatime = timer.GetDeltaTime();
			timer.ResetDeltaTime();
			result += deltatime;
			if(openedWindow.has_value())
			{
			
				if (!glfwWindowShouldClose(openedWindow.value().glfwWin)) SceneManager::NewFrame(deltatime);
				else 
				{
					if (openedWindow.value().vkInstance != nullptr)
					{
						vkDestroyDevice(openedWindow.value().getDevice(), nullptr);

						if (enableValidationLayers) {
							DestroyDebugUtilsMessengerEXT(*(openedWindow.value().vkInstance),
								openedWindow.value().getDebugMessenger(), nullptr);
						}

						vkDestroySurfaceKHR(*(openedWindow.value().vkInstance),
							openedWindow.value().getSurface(), nullptr);

						vkDestroyInstance(*(openedWindow.value().vkInstance), nullptr);
					}

					glfwDestroyWindow(openedWindow.value().glfwWin);

					break;
				}
				glfwSwapBuffers(openedWindow.value().glfwWin);
			}
			LogInfo(format("Average {}:{}\n",statistics_count , result /  statistics_count));
		}
		LogInfo(format("Final Average 1:{}\n" , (result / statistics_count)));
	}
}

int main()
{
	Ningin::Game::Init("Example", WindowOptions::Windowed, new Dimensions2(500, 500), { "Scene" },
		MonoPaths("mono/lib", "example.dll"), false, RenderingApi::Opengl);
	Ningin::Game::Start();
	return 0;
}