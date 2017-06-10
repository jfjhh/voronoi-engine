#include "ellipse.h"

Ellipse::Ellipse(coord rx, coord ry, coord x, coord y, coord t):
	rx(rx), ry(ry)
{
	t      = 0.0;
	center = {x, y, std::max(rx, ry)};
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
	ellipseRGBA(gRenderer, center.x, center.y, rx, ry, 255, 0, 255, 255);
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

