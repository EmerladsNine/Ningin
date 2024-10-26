#pragma once

#include "../../../math/Vector2.h"
#include "../../../math/Vector3.h"
#include <format>

using namespace std;

namespace Ningin
{
	namespace Components
	{
		struct PointCollider
		{
		public:
			int x;
			int y;

			static const PointCollider ZERO;

			PointCollider(int x, int y) : x(x), y(y) {}

			PointCollider() : x(0), y(0) {}
		};

		void PointFromVector2(Vector2& vec, PointCollider& out);

		void PointFromVector3(Vector3& vec, PointCollider& out);

		void PointToString(PointCollider pt, string& out);

	}
}