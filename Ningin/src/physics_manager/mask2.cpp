#include "mask2.h"

using namespace std;

Mask2::Mask2(bool x, bool y) : x(x), y(y)
{
}

Mask2::Mask2() : x(0), y(0)
{
}

pair<bool, bool> Mask2::deconstruct()
{
	return { x, y };
}

string Mask2_toString(Mask2 mask)
{
	return format("Mask2 - x: {}, y: {}", mask.x, mask.y);
}
