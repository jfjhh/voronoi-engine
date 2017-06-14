#include "ellipse.h"

Ellipse::Ellipse(coord rx, coord ry, coord x, coord y, coord t):
	Shape(2.0 * rx, 2.0 * ry),
	rx(rx), ry(ry)
{
	// center.x = x;
	// center.y = y;
	chull.push_back(center);
	setTextureWidth(2.0 * std::max(rx, ry) + 1.0);
}

bool Ellipse::intersects(const Shape& s) const
{
	// return t.intersects(*this);
	return Range{-rx + x, rx + x}.overlaps(s.projectOn(t))
		&& Range{-ry + y, ry + y}.overlaps(s.projectOn(t + (M_PI / 2.0)));
}

bool Ellipse::intersects(const Point& s) const
{
	auto v = s.vcenter();
	return 1.0
		<= pow(((v.x - center.x) / rx), 2)
		+  pow(((v.y - center.y) / ry), 2);
}

void Ellipse::render(void) const
{
	auto x = (textureSide / 2);
	auto y = (textureSide / 2);
	filledEllipseRGBA(gRenderer, x, y, rx, ry, 255, 255, 255, 127);
}

Range Ellipse::project(coord on, Vertex v) const
{
	auto t = cos(on);
	auto c = center.distanceTo({x + v.x, y + v.y}) * t; // Project the center.
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

