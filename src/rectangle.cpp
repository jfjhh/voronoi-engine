#include "rectangle.h"

Rectangle::Rectangle(coord w, coord h, coord x, coord y, coord t):
	Shape(w, h),
	w(w), h(h), hw(w / 2.0), hh(h / 2.0)
{
	chull.push_back({x - hw, y - hw});
	chull.push_back({x - hw, y + hw});
	chull.push_back({x + hw, y - hw});
	chull.push_back({x + hw, y + hw});
	vhull.push_back(center);
}

bool Rectangle::intersects(const Shape& s) const
{
	return Range{-hw, hw}.overlaps(s.projectOn(t))
		&& Range{-hh, hh}.overlaps(s.projectOn(t + (M_PI / 2.0)));
}

void Rectangle::render(void) const
{
	rectangleRGBA(gRenderer,
			center.x - hw, center.y - hh,
			center.x + hw, center.y + hh,
			255, 0, 255, 255);
}

coord Rectangle::width(void) const
{
	return w;
}

coord Rectangle::height(void) const
{
	return h;
}

coord Rectangle::hwidth(void) const
{
	return w / 2;
}

coord Rectangle::hheight(void) const
{
	return h / 2;
}

