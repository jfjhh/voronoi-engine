#include "polygon.h"

Polygon::Polygon(const ConvexHull& v):
	Shape(),
	UnionShape()
{
	chull = v;
	updateTextureSide();
}

Polygon::Polygon(ConvexHull&& v):
	Shape(),
	UnionShape()
{
	chull = std::move(v);
	updateTextureSide();
}

Polygon::Polygon(size_t n, size_t s, coord r):
	Shape(),
	UnionShape()
{
	fputs("(Constructing polygram.)", stderr);
	if (n < 3 || 1 > s || s >= n || r <= 0) {
		throw;
	}

	auto v = ConvexHull{};
	auto dt = 2 * M_PI * s / n;
	for (auto i = 0u; i < n; i++){
		auto t = i * dt;
		v.push_back(Vertex{r * cos(t), r * sin(t)});
	}

	chull = std::move(v);
	updateTextureSide();
}

void Polygon::add(Vertex v)
{
	chull.push_back(v);
	updateTextureSide();
}

bool Polygon::intersects(const Shape& s) const
{
	for (auto it = chull.begin(); it < chull.end() - 1; it++) {
		auto t = it->angleTo(*(it + 1)) + (M_PI / 2.0);
		if (projectOn(t).overlaps(s.projectOn(t))) {
			return true;
		}
	}

	return false;
}

bool Polygon::intersects(const Point& s) const
{
	auto sy = s.vcenter().y;
	auto intersections = 0u;
	for (auto it = chull.begin(); it < chull.end() - 1; it++) {
		auto a = it;
		auto b = it + 1;
		if ((a->y < sy && sy < b->y) || (b->y < sy && sy < a->y)) {
			intersections++;
		}
	}
	return (intersections % 2 == 1);
}

void Polygon::render(void) const
{
	auto verts = vertices();
	auto size  = verts.size();
	auto xs    = std::vector<Sint16>(size);
	auto ys    = std::vector<Sint16>(size);
	auto itx   = xs.begin();
	auto ity   = ys.begin();
	for (const auto& v: verts) {
		*itx++ = v.x + (textureSide / 2);
		*ity++ = v.y + (textureSide / 2);
	}
	filledPolygonRGBA(gRenderer, xs.data(), ys.data(), size, 255, 255, 255, 63);
}

Range Polygon::project(coord on, Vertex v) const
{
	auto r = Range();
	for (const auto& v: chull) {
		r.update(v.project(on, {v.x + x, v.y + y}));
	}
	return r;
}

