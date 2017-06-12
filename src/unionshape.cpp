#include "unionshape.h"

void UnionShape::updateTextureSide(void)
{
	auto v = std::max_element(chull.begin(), chull.end());
	setTextureWidth(2 * ceil(v->distanceTo()));
}

void UnionShape::add(ShapePointer t)
{
	auto c = t->vertices();
	auto v = t->voronoiVertices();
	chull.insert(chull.end(), c.begin(), c.end());
	vhull.insert(vhull.end(), v.begin(), v.end());
	shapes.push_back(t);

	auto vc = VoronoiVertex{};
	for (const auto& s: shapes) {
		vc += s->vcenter();
	}

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
	updateTextureSide();
}

void UnionShape::render(void) const
{
	for (const auto& s: shapes) {
		s->render();
	}
}

void UnionShape::translate(double x, double y)
{
	for (const auto& s: shapes) {
		s->translate(x, y);
	}
	Shape::translate(x, y);
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

void UnionShape::rotate(double by)
{
	for (const auto& s: shapes) {
		s->rotate(by);
	}
	Shape::rotate(by);
}

ShapeUnion UnionShape::shapePointers(void) const
{
	return shapes;
}

