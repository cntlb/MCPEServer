#pragma once

class Color
{
public:
	static const Color BLACK;
	static const Color BLUE;
	static const Color CYAN;
	static const Color GREEN;
	static const Color GREY;
	static const Color NIL;
	static const Color PURPLE;
	static const Color RED;
	static const Color WHITE;
	static const Color YELLOW;

public:
	float r, g, b, a;

public:
	Color();
	Color(float r, float g, float b, float a);

	static Color fromHSB(float h, float s, float v);
};