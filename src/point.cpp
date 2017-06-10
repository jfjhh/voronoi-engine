#include "point.h"

Point::Point(coord x, coord y)
{
	t      = 0.0;
	center = {x, y};
	chull.push_back(center);
	vhull.push_back(center);
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
	pixelRGBA(gRenderer, center.x, center.y, 255, 0, 255, 255);
}

