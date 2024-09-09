#pragma once

#include <cmath>
#include <stdexcept>

static const float PI = 3.1415926f;
static const double EPSILON = 1e-6;

float clamp(float val_to_clamp, float min, float max);
float degrees_to_radians(float deg);
double radical(double number, int n);
