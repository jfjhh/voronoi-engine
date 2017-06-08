#include "shape.h"

void Shape::offset(double x, double y)
{
	std::transform(chull.begin(), chull.end(), chull.begin(),
			[x, y](VertexPointer v) {
			return std::make_shared<Vertex>(v->x + x, v->y + y);
			});
	std::transform(vhull.begin(), vhull.end(), vhull.begin(),
			[x, y](VoronoiVertexPointer v) {
			return std::make_shared<VoronoiVertex>(v->x + x, v->y + y, v->r);
			});
	center.offset(x, y);
}

VoronoiVertex Shape::getCenter(void) const
{
	return center;
}

double Shape::getCenterX(void) const
{
	return center.x;
}

double Shape::getCenterY(void) const
{
	return center.y;
}

double Shape::getVoronoiRadius(void) const
{
	return center.r;
}

ConvexHull Shape::getVertices(void) const
{
	return chull;
}

VoronoiHull Shape::getVoronoiVertices(void) const
{
	return vhull;
}

