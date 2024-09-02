#include "ningin.h"

ResourceManager resourceManager = ResourceManager();
glm::mat4 projectionMatrix = glm::mat4(1.0f);

const int ARRAY_LIMIT = 100;
const int ATLAS_LIMIT = 256;

FT_Library Game::init_freetype()
{
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) // all functions return a value different than 0 whenever an error occurred
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	return ft;
}

void Game::init_gl2d(Dimensions2& dimensions)
{
    glViewport(0, 0, dimensions.width, dimensions.height );
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);
    glDepthFunc(GL_LEQUAL);
}

void Game::init_resource_manager()
{
    // TODO
}
