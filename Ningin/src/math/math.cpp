#include "math.h"

template <typename T>
T Clamp(T valToClamp, T min, T max)
{
	static_assert(std::is_arithmetic<T>::value, "T must be a numeric type");

	if (valToClamp < min)
	{
		return min;
	}
	else if (valToClamp > max)
	{
		return max;
	}
	else
	{
		return valToClamp;
	}
}

float DegreesToRadians(float deg)
{
	return deg * PI / 180.0f;
}

double Radical(double number, int n)
{
	if (number < 0.0 && n % 2 == 0)
	{
		throw std::invalid_argument("Cannot compute even-root of negative number");
	}

	if (number == 0.0)
	{
		return 0.0;
	}

	double x = number;
	double y = 1.0;

	// Iteratively calculate the nth root using Newton's method
	while (std::abs(x - y) > EPSILON)
	{
		x = ((n - 1) * x + number / std::pow(x, n - 1)) / static_cast<double>(n);
		y = number / std::pow(x, n - 1);
	}

	return x;
}
