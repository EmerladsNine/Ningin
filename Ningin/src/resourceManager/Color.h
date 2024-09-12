#pragma once

#include <cstdint>
#include <format>
#include <string>

class Color
{
	public:
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;

		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

		static Color FromRGB(uint8_t rgb);

		static Color FromColor(Color& color, uint8_t a);

		void SetAlpha(uint8_t a);

		std::string ToString();

		static Color DefaultColor();
};
