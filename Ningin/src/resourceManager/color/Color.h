#pragma once

#include <cstdint>
#include <format>
#include <string>

using namespace std;

namespace Ningin
{
	class Color
	{
	public:
		unsigned int r, g, b, a;

		Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
		Color();

		bool operator==(Color& other);
	};

	void ColorFromRGB(unsigned int rgb, Color& out);
	void ColorFromRGBA(unsigned int r, unsigned int g, unsigned int b, unsigned int a, Color& out);
	void ColorFromColor(Color& color, unsigned int a, Color& out);

	void ColorSetAlpha(Color& color, unsigned int a);

	void ColorToString(Color& color, string& out);
}