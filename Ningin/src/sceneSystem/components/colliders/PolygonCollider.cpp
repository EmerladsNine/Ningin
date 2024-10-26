#include "PolygonCollider.h"

namespace Ningin
{
	namespace Components
	{
		void PolygonCollider::AddVertex(Vector2& vertex)
		{
			_vertices.push_back(vertex);
		}

		string PolygonCollider::ToString()
		{
			string polygon_string = std::format("Polygon Pos(x={}, y={})\nVertices:", position.x, position.y);

			int i = 0;
			for (Vector2 vertex : _vertices)
			{
				polygon_string += format("Vertex {}: Pos(x={}. y={})", i, vertex.x, vertex.y);
				i++;
			}

			return polygon_string;
		}

	}
}