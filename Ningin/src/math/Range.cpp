#include "Range.h"

template <typename T>
Range<T>::Range(T min, T max) : min(min), max(max) {}

template <typename T>
Range<T>::Range() : min(T(0)), max(T(10)) {}

template <typename T>
T RangeBoundValue(const Range<T>& range, T val)
{
	return Clamp<T>(val, range.min, range.max);
}

template <typename T>
void RangeToString(Range<T>& range, string& out)
{
	out = format("Range - x: {}, y: {}", range.min, range.max);
}
