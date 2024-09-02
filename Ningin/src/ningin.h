#pragma once

#include "resource_manager/resource_manager.h"
#include "system/window_options.h"
#include "string"
#include "freetype/freetype.h"
#include "GL/glew.h"
#include <glm.hpp>

extern ResourceManager resourceManager;
extern glm::mat4 projectionMatrix;

extern const int ARRAY_LIMIT;
extern const int ATLAS_LIMIT;

class Game {
	public:
		Game(std::string game_name);
		uint16_t new_window(std::string window_name, WindowOptions windowOptions, uint16_t scene_id, Dimensions2& dimensions);
	private:
		FT_Library init_freetype();
		void init_gl2d(Dimensions2 &dimensions);
		void init(WindowOptions windowOptions, Dimensions2 &dimensions, std::vector<std::string>);
		void init_resource_manager();
		void main_loop();

};