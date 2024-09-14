#pragma once

#include <tuple>
#include <format>

using namespace std;

class Mask3
{
	public:
		Mask3(bool x, bool y, bool z);
		Mask3();

		tuple<bool, bool, bool> Deconstruct();

		bool x, y, z;
};

void Mask3ToString(Mask3 mask, string& out);
