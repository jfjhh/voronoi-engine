/**
 * Convex Polygon Class.
 * Alex Striff.
 */

#ifndef POLYGON_H
#define POLYGON_H

#include "ellipse.h"
#include "point.h"
#include "unionshape.h"

class Polygon : public UnionShape
{
	public:
		Polygon(const ConvexHull& v);
		Polygon(ConvexHull&& v);
		Polygon(size_t n = 3u, size_t s = 1u, coord r = 1.0);

		void add(Vertex v);

		bool intersects(const Shape& s) const final override;
		bool intersects(const Point& s) const;
		Range project(coord on = 0.0, Vertex v = {0.0, 0.0}) const;
		void render(void) const override;
};
COMMON_VERIFY(Polygon);

#endif /* POLYGON_H */


