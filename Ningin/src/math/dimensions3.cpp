#include "dimensions3.h"

using namespace std;
/**
 * Creates a new `Dimensions3` instance with the specified width, height, and depth.
 */
Dimensions3::Dimensions3(int width, int height, int depth) : width(width), height(height), depth(depth)
{
}

/**
 * Creates a default `Dimensions3` instance with default values (200, 200, 200).
 */
Dimensions3::Dimensions3() : width(200), height(200), depth(200)
{
}

tuple<int, int, int> Dimensions3::deconstruct()
{
	return std::make_tuple(width, height, depth);
}

string Dimensions3_toString(Dimensions3 dimensions)
{
	return format("Dimensions3 - width: {}, height: {}, depth: {}", dimensions.width,
		dimensions.height, dimensions.depth);
}