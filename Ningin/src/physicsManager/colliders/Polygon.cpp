#include "polygon.h"

using namespace std;

void Polygon::AddVertex(Vector2& vertex)
{
	vertices.push_back(vertex);
}

string Polygon::ToString()
{
	string polygon_string = std::format("Polygon Pos(x={}, y={})\nVertices:", position.x, position.y);
	int i = 0;
	for (Vector2 vertex : vertices) {
		polygon_string += format("Vertex {}: Pos(x={}. y={})", i, vertex.x, vertex.y);
		i++;
	}
}