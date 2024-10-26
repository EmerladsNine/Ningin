#pragma once

#include "../../math/Vector2.h"
#include <vector>
#include <format>

struct PolygonCollider {
	private:
		std::vector<Vector2> _vertices;
	public:
		Vector2 position;

		PolygonCollider(std::vector<Vector2>& vertices, Vector2& position) : _vertices(vertices), position(position) {}

		void AddVertex(Vector2& vertex);
		std::string ToString();
};
