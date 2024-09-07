#include "math.h"

float const math::PI = 3.1415926f;
double const math::EPSILON =1e-6;
float math::clamp(float val_to_clamp, float min, float max) 
{
    if (val_to_clamp < min) {
        return min;
    }
    else if (val_to_clamp > max) {
        return max;
    }
    else {
        return val_to_clamp;
    }
}

float math::degrees_to_radians(float deg)
{
    return deg * PI / 180.0f;
}

double math::radical(double number, int n)
{
    if (number < 0.0 && n % 2 == 0) {
        throw std::invalid_argument("Cannot compute even-root of negative number");
    }

    if (number == 0.0) {
        return 0.0;
    }

    double x = number;
    double y = 1.0;

    // Iteratively calculate the nth root using Newton's method
    while (std::abs(x - y) > EPSILON) {
        x = ((n - 1) * x + number / std::pow(x, n - 1)) / static_cast<double>(n);
        y = number / std::pow(x, n - 1);
    }

    return x;
}
