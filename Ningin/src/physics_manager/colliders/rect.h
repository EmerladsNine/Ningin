#pragma once

#include "../../math/dimensions2.h"
#include "../../math/vector2.h"

class Rect {
public:
	Dimensions2 dimensions;
	Vector2 position;
	Rect(Dimensions2 dimensions, Vector2 position) : dimensions(dimensions), position(position) {}
};
