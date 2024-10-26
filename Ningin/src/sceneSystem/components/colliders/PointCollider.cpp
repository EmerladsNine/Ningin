#include "PointCollider.h"

namespace Ningin
{
	namespace Components
	{
		// Define the ZERO constant.
		const PointCollider PointCollider::ZERO = PointCollider(0, 0);

		void PointFromVector2(Vector2& vec, PointCollider& out)
		{
			out = PointCollider(static_cast<int>(vec.x), static_cast<int>(vec.y));
		}

		void PointFromVector3(Vector3& vec, PointCollider& out)
		{
			out = PointCollider(static_cast<int>(vec.x), static_cast<int>(vec.y));
		}

		void PointToString(PointCollider pt, string& out)
		{
			out = format("Point - x: {}, y: {}", pt.x, pt.y);
		}
	}
}