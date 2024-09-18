#pragma once

#include <cmath>
#include <stdexcept>

static const float PI = 3.1415926f;
static const double EPSILON = 1e-6;

template <typename T>
T Clamp(T valToClamp, T min, T max);

float DegreesToRadians(float deg);

double Radical(double number, int n);
