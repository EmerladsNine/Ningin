#pragma once

#include "Math.h"
#include <format>
#include <type_traits>

using namespace std;

template <typename T>
class Range
{
	static_assert(std::is_arithmetic<T>::value, "T must be a numeric type");

	public:
		T min, max;

		Range(T min, T max);
		Range();
};

template <typename T>
T RangeBoundValue(const Range<T>& range, T val);

template <typename T>
void RangeToString(Range<T>& range, string& out);
