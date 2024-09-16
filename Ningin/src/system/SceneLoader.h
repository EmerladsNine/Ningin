#pragma once

#include "../resourceManager/color/Color.h"
#include "../sceneSystem/Scene.h"
#include "../math/Vector3.h"
#include <cstddef>
#include <string>
#include <vector>

using namespace std;

class SceneLoader
{
	public:
		SceneLoader();

		Scene* GetSceneFromId(size_t sceneId);
		void LoadSceneFromFile(string path);

	private:
		template<typename T> T Read(uint8_t** filePointer);
		template<typename T> T SwapBytes(T value);

		Vector3 ReadVector3(uint8_t** filePointer);
		Color ReadColor(uint8_t** filePointer);

		void AddComponent(uint8_t id, EntityId entityId, World& world,
			const vector<string>& strings, const vector<uint32_t>& propertiesPointers,
			uint8_t* filePropertiesPointer);

		vector<Scene> _scenes;
};
