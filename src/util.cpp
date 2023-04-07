#include "util.h"

#include <cmath>

sf::Color col_from_hsv(float hue, float sat, float val)
{
	float C = sat * val;
	float X = C * (1 - std::abs(std::fmodf(hue / 60.0f, 2) - 1));
	float m = val - C;

	float r, g, b;
	r = g = b = 0.0f;

	if (0 <= hue && hue < 60)
	{
		r = C;
		g = X;
		b = 0.0f;
	}
	else if (60 <= hue && hue < 120)
	{
		r = X;
		g = C;
		b = 0.0f;
	}
	else if (120 <= hue && hue < 180)
	{
		r = 0.0f;
		g = C;
		b = X;
	}
	else if (180 <= hue && hue < 240)
	{
		r = 0.0f;
		g = X;
		b = C;
	}
	else if (240 <= hue && hue < 300)
	{
		r = X;
		g = 0.0f;
		b = C;
	}
	else if (300 <= hue && hue < 360)
	{
		r = C;
		g = 0.0f;
		b = X;
	}

	return sf::Color(
		(int)((r + m) * 255.0f),
		(int)((g + m) * 255.0f),
		(int)((b + m) * 255.0f)
	);
}
