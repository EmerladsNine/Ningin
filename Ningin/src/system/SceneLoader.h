#pragma once

#include "../scene_system/Scene.h"
#include <cstddef>
#include <string>
#include <vector>

class SceneLoader
{
	public:
		SceneLoader();

		Scene GetSceneFromId(std::size_t sceneId);
		void LoadSceneFromFile(std::string path);

	private:
		float ReadFloat(uint8_t** filePointer);
		uint32_t ReadU32(uint8_t** filePointer);
		uint16_t ReadU16(uint8_t** filePointer);
		uint8_t ReadU8(uint8_t** filePointer);

		void AddComponent(uint8_t id, EntityId entityId, World& world,
			const std::vector<std::string>& strings, const std::vector<uint32_t>& propertiesPointers,
			uint8_t* filePropertiesPointer);

		std::vector<Scene> scenes;
};
