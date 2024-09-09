#pragma once

#include <format>
#include <tuple>

class Dimensions3
{
  public:
    int width;
    int height;
    int depth;

    Dimensions3(int width, int height, int depth);

    Dimensions3();

    std::tuple<int, int, int> deconstruct();
};
