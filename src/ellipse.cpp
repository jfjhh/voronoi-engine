#include "ellipse.h"

Ellipse::Ellipse(coord rx, coord ry, coord x, coord y, coord t):
	Shape(2.0 * rx, 2.0 * ry),
	rx(rx), ry(ry)
{
	center.x = x;
	center.y = y;
	chull.push_back(center);
	vhull.push_back(center);
}

bool Ellipse::intersects(const Shape& t) const
{
	return t.intersects(*this);
}

bool Ellipse::intersects(const Point& t) const
{
	auto v = t.vcenter();
	return 1.0
		<= pow(((v.x - center.x) / rx), 2)
		+  pow(((v.y - center.y) / ry), 2);
}

void Ellipse::render(void) const
{
	auto x = (textureSide / 2);
	auto y = (textureSide / 2);
	ellipseRGBA(gRenderer, x, y, rx, ry, 255, 255, 255, 255);
}

Range Ellipse::project(coord on) const
{
	auto t = cos(on);
	auto c = center.distanceTo() * t; // Project the center.
	auto r = (rx * ry) / sqrt((ry*ry - rx*rx) * t*t + rx*rx); // Param. ellipse.
	return Range{c - r, c + r};
}

coord Ellipse::xRadius(void) const
{
	return rx;
}

coord Ellipse::yRadius(void) const
{
	return ry;
}

