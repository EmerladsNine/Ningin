#include "scenes_loader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <stdexcept>
#include <stdlib.h>

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
    float version;
    std::memcpy(&version, filePointer, sizeof(version));
    version = swapFloatBytes(*reinterpret_cast<uint32_t*>(&version)); // Convert from big endian to host endian
    filePointer += 4;

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

        uint32_t headSize;
        std::memcpy(&headSize, filePointer, sizeof(headSize));
        headSize = _byteswap_ulong(headSize);
        filePointer += 4;

        uint32_t objectsSize;
        std::memcpy(&objectsSize, filePointer, sizeof(objectsSize));
        objectsSize = _byteswap_ulong(objectsSize);
        filePointer += 4;

        uint32_t componentsSize;
        std::memcpy(&componentsSize, filePointer, sizeof(componentsSize));
        componentsSize = _byteswap_ulong(componentsSize);
        filePointer += 4;

        uint32_t propertiesSize;
        std::memcpy(&propertiesSize, filePointer, sizeof(propertiesSize));
        propertiesSize = _byteswap_ulong(propertiesSize);
        filePointer += 4;

        uint32_t stringsSize;
        std::memcpy(&stringsSize, filePointer, sizeof(stringsSize));
        stringsSize = _byteswap_ulong(stringsSize);
        filePointer += 4;

        uint32_t componentsPointer = headSize + objectsSize;
        uint32_t propertiesPointer = componentsPointer + componentsSize;
        uint32_t stringsPointer = propertiesPointer + propertiesSize;

        //Read String Section
        filePointer = file.data() + stringsPointer;
        uint8_t* stopPoint = filePointer + stringsSize;
        std::vector<std::string> strings;
        std::string currentString;
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
        
    }
    else {
        throw std::runtime_error("Invalid version of scene file");
    }
}
