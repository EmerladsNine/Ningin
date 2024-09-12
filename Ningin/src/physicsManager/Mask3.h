#pragma once

#include <tuple>
#include <format>

class Mask3
{
public:
	bool x, y, z;

	Mask3(bool x, bool y, bool z);

	Mask3();

	std::tuple<bool, bool, bool> Deconstruct();
};

std::string Mask3ToString(Mask3 mask);
