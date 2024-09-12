#include "renderer.h"
#include "../sceneSystem/components/textRenderer.h"
#include "../sceneSystem/components/spriteRenderer.h"

void RendererSystem(float deltaTime, EntityManager* entityManager)
{
	Text::system(entityManager);
	SpriteRenderer::system(entityManager);
}
