#pragma once

#include "Math.h"
#include <format>

using namespace std;

class Range
{
public:
	float min, max;

	Range(float min, float max);
	Range();
};

float RangeBoundValue(const Range& range, float val);

void RangeToString(Range& range, string& out);
