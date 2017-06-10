#include "unionshape.h"

void UnionShape::add(ShapePointer t)
{
	auto c = t->vertices();
	auto v = t->voronoiVertices();
	chull.insert(chull.end(), c.begin(), c.end());
	vhull.insert(vhull.end(), v.begin(), v.end());
	shapes.push_back(t);

	auto xc = 0.0;
	auto yc = 0.0;
	for (const auto& s: shapes) {
		auto c = s->vcenter();
		xc += c.x;
		yc += c.y;
	}
	auto vc = VoronoiVertex{xc, yc};

	auto max_distance = 0.0;
	auto i = shapes.begin();
	for (auto it = i; it < shapes.end(); it++) {
		auto d = vc.distanceTo((*it)->vcenter());
		if (d > max_distance) {
			max_distance = d;
			i = it;
		}
	}
	vc.r = max_distance + (*i)->vcenter().r;
}

void UnionShape::render(void) const
{
	for (const auto& s: shapes) {
		s->render();
	}
}

void UnionShape::offset(double x, double y)
{
	for (const auto& s: shapes) {
		s->offset(x, y);
	}
	center.offset(x, y);
}

bool UnionShape::intersects(const Shape& t) const
{
	for (const auto& s: shapes) {
		if (t.intersects(*s)) {
			return true;
		}
	}
	return false;
}

Range UnionShape::project(coord on) const
{
	auto r = inverse_range;

	for (const auto& s: shapes) {
		r.update(s->project(on));
	}

	return r;
}

void UnionShape::setAngle(double to)
{
	for (const auto& s: shapes) {
		s->setAngle(to);
	}
	Shape::setAngle(to);
}

ShapeUnion UnionShape::shapePointers(void) const
{
	return shapes;
}

