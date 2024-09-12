#pragma once

#include <algorithm>

enum SurfaceInteractionModes {
	Minimum, // takes the minimum friction/bounciness between the two interacting bodies
	Maximum, // takes the maximum friction/bounciness between the two interacting bodies
	Average, // takes the mean of the friction/bounciness between the two interacting bodies
	Multiply // takes the sum of the friction/bounciness between the two interacting bodies
};

float CalculateValue(SurfaceInteractionModes mode, float v1, float v2);
