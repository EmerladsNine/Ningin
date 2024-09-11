#pragma once

#include <functional>

struct ForceDynamics {

};

struct DefaultForceDynamics : ForceDynamics {
	std::function<float(float)> get_magnitude_func;
	float arg;
};

struct AppliedForceDynamics : ForceDynamics {
	float force_magnitude;
};
