#pragma once

#include "../../math/Dimensions2.h"
#include "../../math/Vector2.h"

class Rect {
	public:
		Dimensions2 dimensions;
		Vector2 position;

		Rect(Dimensions2 dimensions, Vector2 position) : dimensions(dimensions), position(position) {}
};
