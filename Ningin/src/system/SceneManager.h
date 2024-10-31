#pragma once

#include "../sceneSystem/Scene.h"
#include "../utils/Timer.h"

namespace Ningin
{
	class SceneManager
	{
	public:
		static void NewFrame(float deltatime);

		static Scene* currentScene;
	};
}
