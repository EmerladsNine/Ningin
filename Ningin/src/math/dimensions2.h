#pragma once

#include <tuple>
#include <format>

class Dimensions2
{
public:
	uint64_t width;
	uint64_t height;

	Dimensions2(uint64_t width, uint64_t height);

	Dimensions2();

	std::pair<uint64_t, uint64_t> deconstruct();
};

std::string Dimensions2_toString(Dimensions2 dimensions);
