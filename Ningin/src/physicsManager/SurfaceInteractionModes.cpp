#include "SurfaceInteractionModes.h"

float CalculateValue(SurfaceInteractionModes mode, float v1, float v2)
{
	switch (mode)
	{
		case Minimum: return std::min(v1, v2);
		case Maximum: return std::max(v1, v2);
		case Average: return (v1 + v2) / 2;
		case Multiply: return v1 * v2;
		default: return 0;
	}
}
