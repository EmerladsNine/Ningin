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

		bool Equal(Dimensions2 dim);
};

void Dimensions2ToString(Dimensions2& dimensions, string& out);
