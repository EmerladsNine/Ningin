#pragma once

#include <format>

class Mask2
{
	public:
		bool x, y;

		Mask2(bool x, bool y);

		Mask2();

		std::pair<bool, bool> Deconstruct();
};

std::string Mask2ToString(Mask2 mask);
