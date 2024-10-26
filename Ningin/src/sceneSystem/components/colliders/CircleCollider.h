#pragma once

#include "../../../math/Vector2.h"

namespace Ningin
{
	namespace Components
	{
		struct CircleCollider {
		public:
			float radius;
			Vector2 position;
			CircleCollider(float radius, Vector2 position) : radius(radius), position(position) {}
		};
	}
}