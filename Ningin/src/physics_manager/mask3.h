#pragma once

#include <tuple>
#include <format>

class Mask3
{
public:
	bool x, y, z;

	Mask3(bool x, bool y, bool z);

	Mask3();

	std::tuple<bool, bool, bool> deconstruct();
};

std::string Mask3_toString(Mask3 dimensions);
