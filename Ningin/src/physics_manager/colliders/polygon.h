#pragma once

#include "../../math/vector2.h"
#include <vector>
#include <format>

class Polygon {
private:
	std::vector<Vector2> vertices;
public:
	Vector2 position;

	Polygon(std::vector<Vector2>& vertices, Vector2& position) : vertices(vertices), position(position) {}

	void addVertex(Vector2& vertex);
	void toString();
};
