#include "polygon.h"

using namespace std;

void Polygon::addVertex(Vector2& vertex)
{
	vertices.push_back(vertex);
}

void Polygon::toString()
{
	string polygon_string = std::format("Polygon Pos(x={}, y={})\nVertices:", position.x, position.y);
	int i = 0;
	for (Vector2 vertex: vertices) {
		polygon_string += format("Vertex {}: Pos(x={}. y={})", i, vertex.x, vertex.y);
		i++;
	}
}
