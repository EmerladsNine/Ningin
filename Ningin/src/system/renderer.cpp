#include "renderer.h"
#include "../sceneSystem/components/TextRenderer.h"
#include "../sceneSystem/components/SpriteRenderer.h"

void RendererSystem(Timer timer)
{
	TextRenderer::System();
	SpriteRenderer::System();
}
