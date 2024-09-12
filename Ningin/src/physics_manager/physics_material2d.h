#pragma once

#include "SurfaceInteractionModes.h"

struct PhyscicsMaterial2D {
	SurfaceInteractionModes frictionCombineMode;
	SurfaceInteractionModes bounceCombineMode;
	float dynamicFriction;
	float staticFriction;
	float bounciness;
	float density;
};
