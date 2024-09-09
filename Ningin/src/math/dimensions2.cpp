#include "dimensions2.h"

using namespace std;

Dimensions2::Dimensions2(int width, int height) : width(fabs(width)), height(fabs(height))
{
}

Dimensions2::Dimensions2() : width(200), height(200)
{
}

pair<int, int> Dimensions2::deconstruct()
{
    return { width, height };
}

string Dimensions2_toString(Dimensions2 dimensions)
{
    return format("Dimensions2 - width: {}, height: {}", dimensions.width, dimensions.height);
}

