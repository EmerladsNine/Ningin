#pragma once

#include <cmath>
#include <stdexcept>

static const float PI;
static const double EPSILON;

float clamp(float val_to_clamp, float min, float max);
float degrees_to_radians(float deg);
double radical(double number, int n);
