#include "renderer.h"
#include "../sceneSystem/components/TextRenderer.h"
#include "../sceneSystem/components/SpriteRenderer.h"

using namespace Ningin::Components;

void RendererSystem(float deltatime)
{
	TextRenderer::System();
	SpriteRenderer::System();
}
