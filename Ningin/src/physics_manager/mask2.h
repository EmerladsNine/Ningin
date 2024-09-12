#pragma once

#include <format>

class Mask2
{
	public:
		bool x, y;

		Mask2(bool x, bool y);

		Mask2();

		std::pair<bool, bool> deconstruct();
};

std::string Mask2_toString(Mask2 dimensions);
