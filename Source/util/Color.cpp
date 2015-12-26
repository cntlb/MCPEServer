#include "util/Color.h"

const Color Color::BLACK = Color(1.0f, 1.0f, 1.0f, 1.0f);
const Color Color::BLUE = Color(0, 0, 1.0f, 1.0f);
const Color Color::CYAN = Color(0, 0, 0, 1.0f);
const Color Color::GREEN = Color(0, 1.0f, 0, 1.0f);
const Color Color::GREY = Color(0, 0, 0, 1.0f);
const Color Color::NIL = Color(0, 0, 0, 1.0f);
const Color Color::PURPLE = Color(0, 0, 0, 1.0f);
const Color Color::RED = Color(1.0f, 0, 0, 1.0f);
const Color Color::WHITE = Color(0, 0, 0, 1.0f);
const Color Color::YELLOW = Color(0, 0, 0, 1.0f);

Color::Color()
{
	r = 0;
	g = 0;
	b = 0;
	a = 0;
}

Color::Color(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color Color::fromHSB(float h, float s, float v)
{
	double p, q, t, ff;
	long i;
	Color out;

	if (h >= 360.0) h = 0.0;
	h /= 60.0;
	i = (long)h;
	ff = h - i;
	p = v * (1.0 - s);
	q = v * (1.0 - (s * ff));
	t = v * (1.0 - (s * (1.0 - ff)));

	switch (i) {
	case 0:
		out.r = v;
		out.g = t;
		out.b = p;
		break;
	case 1:
		out.r = q;
		out.g = v;
		out.b = p;
		break;
	case 2:
		out.r = p;
		out.g = v;
		out.b = t;
		break;

	case 3:
		out.r = p;
		out.g = q;
		out.b = v;
		break;
	case 4:
		out.r = t;
		out.g = p;
		out.b = v;
		break;
	case 5:
	default:
		out.r = v;
		out.g = p;
		out.b = q;
		break;
	}
	return out;
}