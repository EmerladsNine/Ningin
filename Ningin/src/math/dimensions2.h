#pragma once

#include <format>

class Dimensions2
{
	public:
		unsigned int width;
		unsigned int height;

		Dimensions2(unsigned int width, unsigned int height);

		Dimensions2();

		std::pair<unsigned int, unsigned int> Deconstruct();
};

std::string Dimensions2ToString(Dimensions2 dimensions);
