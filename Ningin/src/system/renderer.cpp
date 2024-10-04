#include "renderer.h"
#include "../sceneSystem/components/TextRenderer.h"
#include "../sceneSystem/components/SpriteRenderer.h"

void RendererSystem(float deltatime)
{
	TextRenderer::System();
	SpriteRenderer::System();
}
