#include "dimensions2.h"

using namespace std;

Dimensions2::Dimensions2(uint64_t width, uint64_t height) : width(width), height(height)
{
}

Dimensions2::Dimensions2() : width(200), height(200)
{
}

pair<uint64_t, uint64_t> Dimensions2::deconstruct()
{
	return { width, height };
}

string Dimensions2_toString(Dimensions2 dimensions)
{
	return format("Dimensions2 - width: {}, height: {}", dimensions.width, dimensions.height);
}