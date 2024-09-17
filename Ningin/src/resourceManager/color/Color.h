#pragma once

#include <cstdint>
#include <format>
#include <string>

using namespace std;

class Color
{
	public:
		uint8_t r, g, b, a;

		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
		Color();
};

void ColorFromRGB(uint8_t rgb, Color& out);
void ColorFromRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a, Color& out);
void ColorFromColor(Color& color, uint8_t a, Color& out);

void ColorSetAlpha(Color& color, uint8_t a);

void ColorToString(Color& color, string& out);
