#pragma once

#include <algorithm>

enum SurfaceInteractionModes {
	Minimum, // takes the minimum value between the two interacting bodies
	Maximum, // takes the maximum value between the two interacting bodies
	Average, // takes the mean of the values between the two interacting bodies
	Multiply // takes the sum of the values between the two interacting bodies
};

float CalculateValue(SurfaceInteractionModes mode, float v1, float v2) {
	switch (mode) {
		case Minimum: return std::min(v1, v2);
		case Maximum: return std::max(v1, v2);
		case Average: return (v1 + v2) / 2;
		case Multiply: return v1 * v2;
	}
}
