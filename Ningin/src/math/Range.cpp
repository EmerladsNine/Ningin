#include "Range.h"

Range::Range(float min, float max) : min(min), max(max) {}

Range::Range() : min(0), max(10) {}

float RangeBoundValue(Range& range, float val)
{
	return Clamp(val, range.min, range.max);
}

void RangeToString(Range& range, string& out)
{
	out = format("Range - x: {}, y: {}", range.min, range.max);
}
