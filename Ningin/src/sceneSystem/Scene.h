#pragma once

#include "../utils/Timer.h"
#include "../scripting/ScriptingEngine.h"
#include <string>

using namespace std;

namespace Ningin
{
	class Scene
	{
		public:
			Scene(string name);

			void InitDefaultComponentSystem();

			template <typename T> static void RegisterComponent()
			{
				EntityManager::RegisterComponent<T>();
				ScriptingEngine::RegisterComponent<T>();
			}

			void NewFrame(float deltatime);

			string name;
			EntityManager entityManager;

	};
}
