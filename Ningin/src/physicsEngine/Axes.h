#pragma once

#include "../math/vector3.h"

namespace Ningin
{
	namespace Physics
	{
		enum Axes {
			X,
			Y,
			Z,
			XY,
			XZ,
			YZ,
			XYZ
		};

		Vector3 GetDirectionVector(Axes axes);
	}
}
