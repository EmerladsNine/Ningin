#pragma once

#include "../sceneSystem/Scene.h"
#include "../utils/Timer.h"

namespace Ningin
{
	class SceneManager
	{
	public:
		SceneManager(Scene* currentScene);

		void NewFrame(float deltatime);

		Scene* currentScene;
	};
}
