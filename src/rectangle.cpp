#include "rectangle.h"

Rectangle::Rectangle(coord w, coord h, coord x, coord y, coord t):
	Shape(w, h),
	w(w), h(h), hw(w / 2.0), hh(h / 2.0)
{
	center = {x, y, std::min(w, h)};
	translate(x, y);
	chull.push_back({x - hw, y - hw});
	chull.push_back({x - hw, y + hw});
	chull.push_back({x + hw, y - hw});
	chull.push_back({x + hw, y + hw});
	setTextureWidth(std::max(w, h) + 1);
}

Rectangle::operator SDL_Rect()
{
	auto v = chull[0];
	return { (int) v.x, (int) v.y, (int) w, (int) h };
}

bool Rectangle::intersects(const Shape& s) const
{
	// auto r = Range{-hh + y, hh + y};
	// fprintf(stderr, "<<Range: %f, %f>> ", r.min, r.max);
	return Range{-hw + x, hw + x}.overlaps(s.projectOn(t))
		&& Range{-hh + y, hh + y}.overlaps(s.projectOn(t + (M_PI / 2.0)));
}

bool Rectangle::intersects(const VoronoiVertex& v) const
{
	fputs("<Rectangle <=> VoronoiVertex!> ", stderr);
	return Range{-hw + x, hw + x}.overlaps(v.project(t))
		&& Range{-hh + y, hh + y}.overlaps(v.project(t + (M_PI / 2.0)));
}

void Rectangle::render(void) const
{
	auto cx = textureSide / 2;
	auto cy = textureSide / 2;
	boxRGBA(gRenderer,
			cx - hw, cy - hh,
			cx + hw, cy + hh,
			255, 255, 255, 127);
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

