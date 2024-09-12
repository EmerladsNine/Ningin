#include "mask3.h"

using namespace std;

Mask3::Mask3(bool x, bool y, bool z) : x(x), y(y), z(z)
{
}

Mask3::Mask3() : x(0), y(0), z(0)
{
}

std::tuple<bool, bool, bool> Mask3::Deconstruct()
{
	return { x, y, z };
}

string Mask3ToString(Mask3 mask)
{
	return format("Mask3 - x: {}, y: {}, z: {}", mask.x, mask.y, mask.z);
}
