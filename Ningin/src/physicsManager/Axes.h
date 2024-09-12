#pragma once

#include "../math/vector3.h"

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
