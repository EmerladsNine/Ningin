#include "dimensions2.h"

using namespace std;

Dimensions2::Dimensions2(int width, int height) : width(width), height(height)
{
}

Dimensions2::Dimensions2() : width(200), height(200)
{
}

tuple<int, int> Dimensions2::deconstruct()
{
    return std::make_tuple(width, height);
}

string Dimensions2_toString(Dimensions2 dimensions)
{
    return format("Dimensions2 - width: {}, height: {}", dimensions.width, dimensions.height);
}

