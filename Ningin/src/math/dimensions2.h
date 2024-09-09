#pragma once

#include <tuple>
#include <format>

class Dimensions2
{
  public:
    int width;
    int height;

    Dimensions2(int width, int height);

    Dimensions2();

    std::tuple<int, int> deconstruct();
};
