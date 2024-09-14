#include "mask2.h"

Mask2::Mask2(bool x, bool y) : x(x), y(y) {}

Mask2::Mask2() : x(0), y(0) {}

pair<bool, bool> Mask2::Deconstruct()
{
	return { x, y };
}

void Mask2ToString(Mask2 mask, string& out)
{
	out = format("Mask2 - x: {}, y: {}", mask.x, mask.y);
}
