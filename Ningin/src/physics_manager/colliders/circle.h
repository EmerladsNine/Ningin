#pragma once

#include "../../math/vector2.h"

class Circle {
public:
	float radius;
	Vector2 position;
	Circle(float radius, Vector2 position) : radius(radius), position(position) {}
};
