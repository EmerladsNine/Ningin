#include "SceneLoader.h"
#include "../sceneSystem/entity/children.h"
#include "../sceneSystem/entity/name.h"
#include "../sceneSystem/entity/parent.h"
#include "../sceneSystem/components/SpriteRenderer.h"
#include "../sceneSystem/components/TextRenderer.h"
#include "../sceneSystem/components/transform.h"
#include "../utils/FileReader.h"
#include "../sceneSystem/components/ScriptVec.h"
#include "../scripting/ScriptingEngine.h"
#include "../scripting/ScriptLanguage.h"
#include "../environment.h"
#include <filesystem>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <string>
#include <vector>

namespace Ningin
{
	using namespace Components;

	union FloatBytes {
		float f;
		uint32_t i;
	};

	SceneLoader::SceneLoader() {}

	static float swapFloatBytes(float value)
	{
		FloatBytes fb{};
		fb.f = value;
		fb.i = _byteswap_ulong(fb.i);

		return fb.f;
	}

	static bool Checksum(uint32_t provided_checksum, const uint8_t* data, size_t length)
	{
		const uint32_t MOD_ADLER = 65521;
		uint32_t a = 1; // Initial value for 'a'
		uint32_t b = 0; // Initial value for 'b'

		for (size_t i = 0; i < length; ++i)
		{
			a = (a + data[i]) % MOD_ADLER;
			b = (b + a) % MOD_ADLER;
		}

		uint32_t calculated_checksum = (b << 16) | a;
		return provided_checksum == calculated_checksum;
	}

	Scene* SceneLoader::GetSceneFromId(size_t sceneId)
	{
		if (sceneId < _scenes.size())
		{
			return &_scenes[sceneId];
		}
		else
		{
			return nullptr;
		}
	}


	void SceneLoader::LoadSceneFromFile(string sceneName)
	{
		string name;
		Scene scene = Scene(name);
		scene.InitDefaultComponentSystem();
		std::filesystem::path path = Environment::GetGameDirectory() / sceneName;
		vector<uint8_t> file = FileReader::ReadFileBytes(path);

		if (file.size() < 32)
		{
			throw runtime_error("File is too small to contain valid data.");
		}

		uint8_t* filePointer = file.data();

		// Check file format.
		const vector<uint8_t> expectedFormat = { 'N', 'G', 'I', 'N' };
		if (memcmp(filePointer, expectedFormat.data(), expectedFormat.size()) != 0)
		{
			throw runtime_error("Wrong Scene Format Given");
		}

		filePointer += 4;

		// Check Version.
		float version = Read<float>(&filePointer);
		if (version != 1.0f) {
			throw std::runtime_error("Invalid version of scene file");
		}

		// Read Checksum.
		uint32_t checksum;
		memcpy(&checksum, filePointer, sizeof(checksum));
		checksum = _byteswap_ulong(checksum);
		filePointer += 4;

		if (!Checksum(checksum, filePointer, file.size() - 12))
		{
			throw runtime_error("File is corrupted");
		}

		// Reading Header Section.
		uint32_t headSize = Read<uint32_t>(&filePointer);
		uint32_t objectsSize = Read<uint32_t>(&filePointer);
		uint32_t componentsSize = Read<uint32_t>(&filePointer);
		uint32_t propertiesSize = Read<uint32_t>(&filePointer);
		uint32_t stringsSize = Read<uint32_t>(&filePointer);

		uint32_t componentsPointer = headSize + objectsSize;
		uint32_t propertiesPointer = componentsPointer + componentsSize;
		uint32_t stringsPointer = propertiesPointer + propertiesSize;

		// Read String Section
		filePointer = file.data() + stringsPointer;
		uint8_t* stopPoint = filePointer + stringsSize;
		vector<string> strings;
		string currentString;
		auto fileComponentPointer = file.data() + componentsPointer;
		auto filePropertiesPointer = file.data() + propertiesPointer;

		for (; filePointer < stopPoint; filePointer++)
		{
			if (*filePointer == 0)
			{
				strings.push_back(currentString);
				currentString.clear();
			}
			else
			{
				currentString.push_back(static_cast<char>(*filePointer));
			}
		}

		// Set Scene name
		scene.name = strings[0];

		// Read Entities
		filePointer = file.data() + headSize;
		stopPoint = filePointer + objectsSize;

		// create a scene entity so ids will start from 1 not 0
		scene.entityManager.CreateNewEntity();

		while (filePointer < stopPoint)
		{
			EntityId entityId = scene.entityManager.CreateNewEntity();
			// This Contains the entity id .. which is the same given from the function new_entity().
			filePointer += 4;

			// The name of the entity
			uint32_t nameIndex = Read<uint32_t>(&filePointer);
			Name* name = new Name(strings[nameIndex]);
			scene.entityManager.AddComponent(entityId, typeid(Name), name);

			// parent id
			uint32_t parentIndex = Read<uint32_t>(&filePointer);
			Parent* parent = new Parent(parentIndex);
			scene.entityManager.AddComponent(entityId, typeid(Parent), parent);

			// Children
			Children* children = new Children(vector<EntityId>{});
			scene.entityManager.AddComponent(entityId, typeid(Children), children);

			uint16_t componentsCount = Read<uint16_t>(&filePointer);
			uint16_t componentPosition = 0;

			while (componentPosition < componentsCount) {
				uint32_t pointer = Read<uint32_t>(&filePointer);
				auto currentPointer = fileComponentPointer + pointer;

				uint8_t componentId = Read<uint8_t>(&currentPointer);
				uint16_t propertiesCount = Read<uint16_t>(&currentPointer);
				uint16_t propertyPosition = 0;

				vector<uint32_t> properties;

				while (propertyPosition < propertiesCount) {
					properties.push_back(Read<uint32_t>(&currentPointer));
					propertyPosition++;
				}

				AddComponent(componentId, entityId, scene.entityManager, strings, properties,
					filePropertiesPointer);

				componentPosition++;
			}

			uint16_t scriptsCount = Read<uint16_t>(&filePointer);
			uint16_t scriptPositon = 0;
			
			ScriptVec* scriptVec = new ScriptVec();

			while (scriptPositon < scriptsCount)
			{
				string scriptName = strings[Read<uint32_t>(&filePointer)];
				//Implement multiple language script in Scene Loader !
				Scriptable* script = ScriptingEngine::GetScript(entityId, scriptName, ScriptLanguage::CSHARP);
				scriptVec->scripts.push_back(script);
				scriptPositon++;
			}

			scene.entityManager.AddComponent(entityId, typeid(ScriptVec), scriptVec);

			if (parentIndex != 0)
			{
				Children* parentChildren = static_cast<Children*>(scene.entityManager.GetComponent(parentIndex, typeid(Children)));
				parentChildren->children.push_back(entityId);
			}
		}
		_scenes.push_back(std::move(scene));
	}

	void SceneLoader::AddComponent(uint8_t id, EntityId entityId, EntityManager& entityManager, const vector<string>& strings,
		const vector<uint32_t>& propertiesPointers, uint8_t* filePropertiesPointer)
	{
		switch (id)
		{
			case 0:
			{
				Transform* transform = new Transform();
				for (uint32_t propertyPointer : propertiesPointers)
				{
					auto currentPointer = filePropertiesPointer + propertyPointer;
					string name = strings[Read<uint32_t>(&currentPointer)];

					if (name == "Position")
					{
						Vector3 position = ReadVector3(&currentPointer);
						transform->position = position;
					}
					else if (name == "Rotation")
					{
						Vector3 rotation = ReadVector3(&currentPointer);
						transform->rotation = rotation;
					}
					else if (name == "Scale")
					{
						Vector3 scale = ReadVector3(&currentPointer);
						transform->scale = scale;
					}
				}

				entityManager.AddComponent(entityId, typeid(Transform), transform);
				break;
			}

			case 1:
			{
				bool alpha = false;
				bool useTint = true;
				Color tintingColor;
				string shader = "";
				string textureName = "";

				for (uint32_t propertyPointer : propertiesPointers)
				{
					auto currentPointer = filePropertiesPointer + propertyPointer;
					string name = strings[Read<uint32_t>(&currentPointer)];

					if (name == "TextureName")
					{
						textureName = strings[Read<uint32_t>(&currentPointer)];
					}
					else if (name == "TintingColor")
					{
						tintingColor = ReadColor(&currentPointer);
					}
					else if (name == "UseTint")
					{
						useTint = Read<bool>(&currentPointer);
					}
					else if (name == "useAlpha")
					{
						alpha = Read<bool>(&currentPointer);
					}
					else if (name == "Shader")
					{
						shader = strings[Read<uint32_t>(&currentPointer)];
					}
				}

				SpriteRenderer* sprite = new SpriteRenderer(textureName, shader, tintingColor, useTint, alpha);
				entityManager.AddComponent(entityId, typeid(SpriteRenderer), sprite);
				break;
			}

			case 2:
			{
				Color textColor;
				string shader = "";
				string fontName = "";
				uint8_t fontSize = 0;
				string text = "";
				bool useMultiLine = false;

				for (uint32_t propertyPointer : propertiesPointers)
				{
					auto currentPointer = filePropertiesPointer + propertyPointer;
					string name = strings[Read<uint32_t>(&currentPointer)];

					if (name == "FontName")
					{
						fontName = strings[Read<uint32_t>(&currentPointer)];
					}
					else if (name == "FontSize")
					{
						fontSize = Read<uint8_t>(&currentPointer);
					}
					else if (name == "TextColor")
					{
						textColor = ReadColor(&currentPointer);
					}
					else if (name == "Text")
					{
						text = strings[Read<uint32_t>(&currentPointer)];
					}
					else if (name == "Shader")
					{
						shader = strings[Read<uint32_t>(&currentPointer)];
					}
					else if (name == "UseMultiLine")
					{
						useMultiLine = Read<bool>(&currentPointer);
					}
				}

				TextRenderer* textRenderer = new TextRenderer(fontName, shader, textColor, text, fontSize,
					useMultiLine);

				entityManager.AddComponent(entityId, typeid(TextRenderer), textRenderer);
				break;
			}

			default: break;
		}
	}

	Vector3 SceneLoader::ReadVector3(uint8_t** filePointer) {
		float x = Read<float>(filePointer);
		float y = Read<float>(filePointer);
		float z = Read<float>(filePointer);
		return Vector3(x, y, z);
	}

	Color SceneLoader::ReadColor(uint8_t** filePointer) {

		uint8_t r = Read<uint8_t>(filePointer);
		uint8_t g = Read<uint8_t>(filePointer);
		uint8_t b = Read<uint8_t>(filePointer);
		uint8_t a = Read<uint8_t>(filePointer);

		return Color(r, g, b, a);
	}

	template<typename T>
	T SceneLoader::Read(uint8_t** filePointer) {
		if (is_same<T, bool>::value) return Read<uint8_t>(filePointer) != 0;

		T value;
		memcpy(&value, *filePointer, sizeof(value));
		value = SwapBytes(value);
		*filePointer += sizeof(value);
		return value;
	}

	template<typename T>
	T SceneLoader::SwapBytes(T value) {
		if (is_same<T, float>::value)
			value = static_cast<T>(swapFloatBytes(static_cast<float>(value)));

		else if (is_same<T, uint32_t>::value)
			value = static_cast<T>(_byteswap_ulong(static_cast<unsigned long>(value)));

		else if (is_same<T, uint16_t>::value)
			value = static_cast<T>(_byteswap_ushort(static_cast<unsigned short>(value)));

		else if (is_same<T, uint8_t>::value) value = value;

		return value;
	}
}
