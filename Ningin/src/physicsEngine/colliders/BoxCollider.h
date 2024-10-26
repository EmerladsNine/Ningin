#pragma once

#include "../../math/Dimensions2.h"
#include "../../math/Vector2.h"

struct BoxCollider {
	public:
		Dimensions2 dimensions;
		Vector2 position;

		BoxCollider(Dimensions2 dimensions, Vector2 position) : dimensions(dimensions), position(position) {}
};
