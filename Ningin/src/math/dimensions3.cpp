#include "dimensions3.h"

Dimensions3::Dimensions3(unsigned int width, unsigned int height, unsigned int depth) : width(width),
	height(height), depth(depth) {}

Dimensions3::Dimensions3() : width(200), height(200), depth(200) {}

tuple<unsigned int, unsigned int, unsigned int> Dimensions3::Deconstruct()
{
	return make_tuple(width, height, depth);
}

void Dimensions3ToString(Dimensions3& dimensions, string& out)
{
	out = format("Dimensions3 - width: {}, height: {}, depth: {}", dimensions.width, dimensions.height,
		dimensions.depth);
}
