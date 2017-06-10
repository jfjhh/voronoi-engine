#include "shape.h"

void Shape::rotate(coord by)
{
	setAngle(t + by);
}

coord Shape::angle(void) const
{
	return t;
}

void Shape::offset(coord x, coord y)
{
	for (auto&& v: chull) {
		v.offset(x, y);
	}
	for (auto&& v: vhull) {
		v.offset(x, y);
	}
	center.offset(x, y);
}

void Shape::setAngle(coord to)
{
	t = to;
}

Range Shape::projectOn(coord axis) const
{
	return project(t - axis);
}

Range Shape::project(coord on) const
{
	auto r = inverse_range;

	for (const auto& v: chull) {
		r.update(v.distanceTo() * cos(on));
	}

	return r;
}

VoronoiVertex Shape::vcenter(void) const
{
	return center;
}

ConvexHull Shape::vertices(void) const
{
	return chull;
}

VoronoiHull Shape::voronoiVertices(void) const
{
	return vhull;
}

