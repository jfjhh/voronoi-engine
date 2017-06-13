#include "point.h"

Point::Point(coord x, coord y):
	Shape()
{
	chull.push_back(center);
	setTextureWidth(5.0);
}

Point::Point(Vertex v):
	Shape()
{
	chull.push_back({v.x, v.y});
}

bool Point::intersects(const Shape& t) const
{
	return t.intersects(*this);
}

bool Point::intersects(const Point& t) const
{
	auto v = t.vcenter();
	return (center.x == v.x && center.y == v.y);
}

void Point::render(void) const
{
	auto x = (textureSide / 2);
	auto y = (textureSide / 2);
	filledCircleRGBA(gRenderer, x, y, 2, 255, 255, 255, 255);
}

