#pragma once

#include <format>

using namespace std;

class Mask2
{
	public:
		Mask2(bool x, bool y);
		Mask2();

		pair<bool, bool> Deconstruct();

		bool x, y;
};

string Mask2ToString(Mask2 mask);
