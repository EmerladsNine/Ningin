#pragma once

#include "../../math/Vector2.h"
#include <vector>
#include <format>

class Polygon {
	private:
		std::vector<Vector2> vertices;
	public:
		Vector2 position;

		Polygon(std::vector<Vector2>& vertices, Vector2& position) : vertices(vertices), position(position) {}

		void AddVertex(Vector2& vertex);
		std::string ToString();
};
