#pragma once

#include <format>
#include <tuple>

using namespace std;

class Dimensions3
{
	public:
		unsigned int width;
		unsigned int height;
		unsigned int depth;

		Dimensions3(unsigned int width, unsigned int height, unsigned int depth);

		Dimensions3();

		std::tuple<unsigned int, unsigned int, unsigned int> Deconstruct();
};

void Dimensions3ToString(Dimensions3& dimensions, string& out);
