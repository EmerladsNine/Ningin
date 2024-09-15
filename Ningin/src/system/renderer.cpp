#include "renderer.h"
#include "../sceneSystem/components/TextRenderer.h"
#include "../sceneSystem/components/SpriteRenderer.h"

void RendererSystem(EntityManager* entityManager,Timer timer)
{
	TextRenderer::System(entityManager);
	SpriteRenderer::System(entityManager);
}
