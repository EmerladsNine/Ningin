#include "scenes_loader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <stdexcept>
#include <stdlib.h>
#include "../math/vector3.h"
#include "../scene_system/components/name.h"
#include "../scene_system/components/parent.h"
#include "../scene_system/components/children.h"
#include "../scene_system/components/transform.h"
#include "../scene_system/components/sprite_renderer.h"
#include "../scene_system/components/text_renderer.h"
#include "../resource_manager/color.h"

union FloatBytes {
    float f;
    uint32_t i;
};
static float swapFloatBytes(float value)
{
    FloatBytes fb;
    fb.f = value;
    fb.i = _byteswap_ulong(fb.i);

    return fb.f;
}

static bool Checksum(uint32_t provided_checksum, const uint8_t* data, std::size_t length) {
    const uint32_t MOD_ADLER = 65521;
    uint32_t a = 1; // Initial value for 'a'
    uint32_t b = 0; // Initial value for 'b'

    for (std::size_t i = 0; i < length; ++i) {
        a = (a + data[i]) % MOD_ADLER;
        b = (b + a) % MOD_ADLER;
    }

    uint32_t calculated_checksum = (b << 16) | a;
    return provided_checksum == calculated_checksum;
}



static std::vector<uint8_t> readFileBytes(const std::string& path) {
    std::ifstream file(path, 
        std::ios::binary //Ensures that the file's content is read or written in binary format
        | std::ios::ate //Immediately positions the file pointer at the end of the file after opening
    );

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + path);
    }

    //Get file size by getting the position at the end of file.
    std::ifstream::pos_type fileSize = file.tellg();

    //Position the file pointer to the beginning of the file.
    file.seekg(0, //Offset
        std::ios::beg //Offset is relative to the begining of the file.
    );

    //Read file contents into byte vector.
    std::vector<uint8_t> buffer(fileSize);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), fileSize)) {
        throw std::runtime_error("Failed to read file: " + path);
    }

    return buffer;
}

SceneLoader::SceneLoader(){}

Scene SceneLoader::GetSceneFromId(std::size_t sceneId)
{
    if (sceneId < scenes.size()) {
        return scenes[sceneId];  
    }
    else {
        throw std::out_of_range("Scene ID out of range");
    }
}

void SceneLoader::LoadSceneFromFile(std::string path)
{
    std::string name;
    Scene scene = Scene(name);
    std::vector<uint8_t> file = readFileBytes(path);
    
    if (file.size() < 32) {
        throw std::runtime_error("File is too small to contain valid data.");
    }

    uint8_t* filePointer = file.data();

    //Check file format.
    const std::vector<uint8_t> expectedFormat = { 'N', 'G', 'I', 'N' };
    if (std::memcmp(filePointer, expectedFormat.data(), expectedFormat.size()) != 0) {
        throw std::runtime_error("Wrong Scene Format Given");
    }
    filePointer += 4;

    //Check Version.
    float version = ReadFloat(&filePointer);

    if (version == 1.0f)
    {
        //Read Checksum.

        uint32_t checksum;
        std::memcpy(&checksum, filePointer, sizeof(checksum));
        checksum = _byteswap_ulong(checksum);
        filePointer += 4;
        if (!Checksum(checksum,filePointer,file.size() - 12))
        {
            throw std::runtime_error("File is corrupted");
        }

        //Reading Header Section.
        uint32_t headSize = ReadU32(&filePointer);
        uint32_t objectsSize = ReadU32(&filePointer);
        uint32_t componentsSize = ReadU32(&filePointer);
        uint32_t propertiesSize = ReadU32(&filePointer);
        uint32_t stringsSize = ReadU32(&filePointer);

        uint32_t componentsPointer = headSize + objectsSize;
        uint32_t propertiesPointer = componentsPointer + componentsSize;
        uint32_t stringsPointer = propertiesPointer + propertiesSize;

        //Read String Section
        filePointer = file.data() + stringsPointer;
        uint8_t* stopPoint = filePointer + stringsSize;
        std::vector<std::string> strings;
        std::string currentString;
        auto fileComponentPointer = file.data() + componentsPointer;
        auto filePropertiesPointer = file.data() + propertiesPointer;

        for (;filePointer < stopPoint;filePointer++)
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

        //Set Scene name
        scene.name = strings[0];

        //Read Entities 
        filePointer = file.data() + headSize;
        stopPoint = filePointer + objectsSize;
        
        //create a scene entity so ids will start from 1 not 0
        scene.world.NewEntity();

        while (filePointer < stopPoint)
        {
            EntityId entityId = scene.world.NewEntity();
            // This Contains the entity id .. which is the same given from the function new_entity().
            filePointer += 4;
            
            //The name of the entity
            uint32_t nameIndex = ReadU32(&filePointer);
            Name* name =  new Name(strings[nameIndex]);
            scene.world.entityManager.AddComponent(entityId, typeid(Name), name);

            //parent id
            uint32_t parentIndex = ReadU32(&filePointer);
            Parent* parent = new Parent(parentIndex);
            scene.world.entityManager.AddComponent(entityId, typeid(Parent), parent);
            //Children
            Children* children = new Children(std::vector<EntityId>{});
            scene.world.entityManager.AddComponent(entityId, typeid(Children), children);

            uint16_t componentsCount = ReadU16(&filePointer);
            uint16_t componentPosition = 0;
            while (componentPosition < componentsCount)
            {
                uint32_t pointer = ReadU32(&filePointer);
                auto currentPointer = fileComponentPointer + pointer;
                uint8_t componentId = ReadU8(&currentPointer);
                uint16_t propertiesCount = ReadU16(&currentPointer);
                uint16_t propertyPosition = 0;
                std::vector<uint32_t> properties;
                while (propertyPosition < propertiesCount)
                {
                    properties.push_back(ReadU32(&currentPointer));
                    propertyPosition++;
                }
                AddComponent(componentId, entityId, scene.world, strings, properties, filePropertiesPointer);
                componentPosition++;
            }
            uint16_t scriptsCount = ReadU16(&filePointer);
            uint16_t scriptPositon = 0;
            //Todo Scripting
        }
    }
    else {
        throw std::runtime_error("Invalid version of scene file");
    }
}

void SceneLoader::AddComponent(uint8_t id, EntityId entityId, World& world, const std::vector<std::string>& strings, const std::vector<uint32_t>& propertiesPointers, uint8_t* filePropertiesPointer)
{
    switch (id)
    {
    case 0:
    {
        Transform* transform = new Transform();
        for (uint32_t propertyPointer : propertiesPointers)
        {
            auto currentPointer = filePropertiesPointer + propertyPointer;
            std::string name = strings[ReadU32(&currentPointer)];
            if (name == "Position") {
                Vector3 pos(ReadFloat(&currentPointer), ReadFloat(&currentPointer), ReadFloat(&currentPointer));
                transform->setPosition(pos);
            }
            else if (name == "Rotation") {
                Vector3 rot(ReadFloat(&currentPointer), ReadFloat(&currentPointer), ReadFloat(&currentPointer));
                transform->setRotation(rot);
            }
            else if (name == "Scale") {
                Vector3 scale(ReadFloat(&currentPointer), ReadFloat(&currentPointer), ReadFloat(&currentPointer));
                transform->setScale(scale);
            }
        }
        world.entityManager.AddComponent(entityId,typeid(Transform), transform);
        break;
    }
    case 1:
    {
        bool alpha = false;
        bool useTint = true;
        Color tintingColor = Color::defaultColor();
        std::string shader = "";
        std::string textureName = "";
        for (uint32_t propertyPointer : propertiesPointers)
        {
            auto currentPointer = filePropertiesPointer + propertyPointer;
            std::string name = strings[ReadU32(&currentPointer)];
            if (name == "TextureName") {
                textureName = strings[ReadU32(&currentPointer)];
            }
            else if (name == "TintingColor") {
                tintingColor = Color(ReadU8(&currentPointer), ReadU8(&currentPointer), ReadU8(&currentPointer), ReadU8(&currentPointer));
            }
            else if (name == "UseTint") {
                useTint = ReadU8(&currentPointer) != 0;
            }
            else if (name == "Alpha") {
                alpha = ReadU8(&currentPointer) != 0;
            }
            else if (name == "Shader") {
                shader = strings[ReadU32(&currentPointer)];
            }
        }
        SpriteRenderer* sprite = new SpriteRenderer(textureName, shader, tintingColor, useTint, alpha);
        world.entityManager.AddComponent(entityId, typeid(Sprite), sprite);
        break;
    }
    case 2:
    {
        Color textColor = Color::defaultColor();
        std::string shader = "";
        std::string fontName = "";
        uint8_t fontSize = 0;
        std::string text = "";
        for (uint32_t propertyPointer : propertiesPointers)
        {
            auto currentPointer = filePropertiesPointer + propertyPointer;
            std::string name = strings[ReadU32(&currentPointer)];
            if (name == "FontName") {
                fontName = strings[ReadU32(&currentPointer)];
            }
            else if (name == "FontSize") {
                fontSize = ReadU8(&currentPointer);
            }
            else if (name == "TextColor") {
                textColor = Color(ReadU8(&currentPointer), ReadU8(&currentPointer), ReadU8(&currentPointer), ReadU8(&currentPointer));
            }
            else if (name == "Text") {
                text = strings[ReadU32(&currentPointer)];
            }
            else if (name == "Shader") {
                shader = strings[ReadU32(&currentPointer)];
            }
        }
        Text* text_renderer = new Text(fontName, shader, textColor, text, fontSize);
        world.entityManager.AddComponent(entityId, typeid(Text), text_renderer);
        break;
    }
    default:
        break;
    }
}

float SceneLoader::ReadFloat(uint8_t** filePointer)
{
    float f;
    std::memcpy(&f, filePointer, sizeof(f));
    f = swapFloatBytes(f);
    *filePointer += 4;
    return f;
}

uint32_t SceneLoader::ReadU32(uint8_t** filePointer)
{
    uint32_t i;
    std::memcpy(&i, *filePointer, sizeof(i));
    i = static_cast<uint16_t>(_byteswap_ulong(i));
    *filePointer += 4;
    return i;
}

uint16_t SceneLoader::ReadU16(uint8_t** filePointer)
{
    uint16_t i;
    std::memcpy(&i, *filePointer, sizeof(i));
    i = static_cast<uint16_t>(_byteswap_ulong(i));
    *filePointer += 2;
    return i;
}

uint8_t SceneLoader::ReadU8(uint8_t** filePointer)
{
    uint8_t i;
    std::memcpy(&i, *filePointer, sizeof(i));
    i = static_cast<uint8_t>(_byteswap_ulong(i));
    *filePointer += 1;
    return i;
}

