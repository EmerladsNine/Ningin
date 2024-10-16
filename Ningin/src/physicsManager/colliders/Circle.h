#pragma once

#include "../../math/Vector2.h"

class Circle {
public:
	float radius;
	Vector2 position;
	Circle(float radius, Vector2 position) : radius(radius), position(position) {}
};