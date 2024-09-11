#pragma once

#include <format>
#include <tuple>

class Dimensions3
{
public:
	uint64_t width;
	uint64_t height;
	uint64_t depth;

	Dimensions3(uint64_t width, uint64_t height, uint64_t depth);

	Dimensions3();

	std::tuple<uint64_t, uint64_t, uint64_t> deconstruct();
};

std::string Dimensions3_toString(Dimensions3 dimensions);
