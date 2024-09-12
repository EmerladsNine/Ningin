#include "renderer.h"
#include "../scene_system/components/text_renderer.h"
#include "../scene_system/components/sprite_renderer.h"

void RendererSystem(float deltatime, EntityManager* entityManager)
{
	Text::system(entityManager);
	SpriteRenderer::system(entityManager);
}