#pragma once

#include <functional>

namespace Ningin
{
	namespace Physics
	{
		struct ForceDynamics {

		};

		struct DefaultForceDynamics : ForceDynamics {
			std::function<float(float)> getMagnitudeFunc;
			float arg;
		};

		struct AppliedForceDynamics : ForceDynamics {
			float forceMagnitude;
		};
	}
}