#pragma once

#include <format>

using namespace std;

class Dimensions2
{
	public:
		unsigned int width;
		unsigned int height;

		Dimensions2(unsigned int width, unsigned int height);

		Dimensions2();

		std::pair<unsigned int, unsigned int> Deconstruct();
};

void Dimensions2ToString(Dimensions2& dimensions, string& out);
