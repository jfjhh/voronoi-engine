#include "unionshape.h"

void UnionShape::add(ShapePointer t)
{
	ConvexHull  c = t->getVertices();
	VoronoiHull v = t->getVoronoiVertices();
	chull.insert(chull.end(), c.begin(), c.end());
	vhull.insert(vhull.end(), v.begin(), v.end());
	shapes.push_back(t);

	double xc = 0;
	double yc = 0;
	std::for_each(shapes.begin(), shapes.end(),
			[&xc](ShapePointer u) { xc += u->getCenterX(); });
	std::for_each(shapes.begin(), shapes.end(),
			[&yc](ShapePointer u) { yc += u->getCenterY(); });

	VoronoiVertex vc(xc, yc);
	std::vector<double> distances;
	std::transform(shapes.begin(), shapes.end(), distances.begin(),
			[&vc](ShapePointer u) { return vc.distanceTo(u->getCenter()); });
	auto it = std::max_element(distances.begin(), distances.end());
	vc.r = (*it) + shapes[it - distances.begin()]->getVoronoiRadius();
}

void UnionShape::offset(double x, double y)
{
	std::for_each(shapes.begin(), shapes.end(),
			[x, y](ShapePointer u) { u->offset(x, y); });
	center.offset(x, y);
}

bool UnionShape::intersects(ShapePointer t) const
{
	for (size_t i = 0; i < shapes.size(); i++) {
		if (t->intersects(shapes[i])) {
			return true;
		}
	}
	return false;
}

void UnionShape::render(void) const
{
	std::for_each(shapes.begin(), shapes.end(),
			[](ShapePointer u) { u->render(); });
}

