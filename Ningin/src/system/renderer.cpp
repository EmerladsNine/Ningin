#include "renderer.h"
#include "../sceneSystem/components/TextRenderer.h"
#include "../sceneSystem/components/SpriteRenderer.h"

void RendererSystem(float deltaTime, EntityManager* entityManager)
{
	TextRenderer::System(entityManager);
	SpriteRenderer::System(entityManager);
}
