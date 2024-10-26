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

void Mask2ToString(Mask2 mask, string& out);
