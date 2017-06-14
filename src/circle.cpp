#include "circle.h"

Circle::Circle(coord x, coord y, coord r):
	Shape(2 * r),
	Ellipse(r, r, x, y, 0.0)
{
	rx = r;
	ry = r;
}

bool Circle::intersects(const Circle& s) const
{
    fputs("<<O>>", stderr);
	auto v = s.vcenter();

	// Check if the squared sum of the radii is greater than the
	// squared distance between centers.
	return pow(rx + v.r, 2)
		>  pow(center.x + x - v.x - s.x, 2)
		+  pow(center.y + x - v.y - s.y, 2);
}

void Circle::render(void) const
{
	auto x = (textureSide / 2);
	auto y = (textureSide / 2);
	filledCircleRGBA(gRenderer, x, y, rx, 255, 255, 255, 127);
}

coord Circle::radius(void) const
{
	return rx;
}

Range Circle::project(coord on, Vertex v) const
{
	auto c = distance({x + v.x, y + v.y}) * cos(on); // Project the center.
	// fprintf(stderr, "\t\t(%f, %f, {%f}) \r", c - rx, c + ry, on);
	return Range{c - rx, c + rx};
}

