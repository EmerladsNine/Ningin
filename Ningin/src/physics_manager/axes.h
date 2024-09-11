#pragma once

#include "../math/vector3.h"

enum Axes {
	X,
	Y,
	Z,
	XY,
	XZ,
	YZ,
	XYZ,
};

Vector3 getDirectionVector(Axes axes) {
    switch (axes) {
    case X: return Vector3::UNIT_X;
    case Y: return Vector3::UNIT_Y;
    case Z: return Vector3::UNIT_Z;
    case XY: return Vector3::UNIT_XY;
    case XZ: return Vector3::UNIT_XZ;
    case YZ: return Vector3::UNIT_YZ;
    case XYZ: return Vector3::ONE;
    }
}