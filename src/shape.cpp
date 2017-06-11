#include "shape.h"

void Shape::translate(coord x, coord y)
{
	for (auto&& v: chull) {
		v.translate(x, y);
	}
	for (auto&& v: vhull) {
		v.translate(x, y);
	}
	center.translate(x, y);
}

void Shape::setAngle(coord to)
{
	t = to;
}

void Shape::rotate(coord by)
{
	setAngle(t + by);
}

coord Shape::angle(void) const
{
	return t;
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
	auto h = ConvexHull{};
	for (const auto& v: chull) {
		h.push_back(v.rotate(t));
	}
	return h;
}

VoronoiHull Shape::voronoiVertices(void) const
{
	// TODO: Add in voronoi approximation levels.
	// I.e. the default is the circumcircle (or should it be incircle?)
	// voronoi vertex (vcenter), then the next is the inscribed circle and N
	// tangent circles, for a polygon with N convex hull vertices, or N=2 for a
	// 3-circle ellipse, N=3 gives a 6-circle ellipse, etc. as a pseudo-fractal.
	auto h = VoronoiHull{};
	for (const auto& v: vhull) {
		h.push_back(v.rotate(t));
	}
	return h;
}

