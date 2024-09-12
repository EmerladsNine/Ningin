#include "dimensions2.h"

using namespace std;

Dimensions2::Dimensions2(unsigned int width, unsigned int height) : width(width), height(height)
{
}

Dimensions2::Dimensions2() : width(200), height(200)
{
}

pair<unsigned int, unsigned int> Dimensions2::Deconstruct()
{
	return { width, height };
}

string Dimensions2ToString(Dimensions2 dimensions)
{
	return format("Dimensions2 - width: {}, height: {}", dimensions.width, dimensions.height);
}