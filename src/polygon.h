/**
 * Convex Polygon Class.
 * Alex Striff.
 */

#ifndef POLYGON_H
#define POLYGON_H

// #include <unordered_set>
#include <set>
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
		Range project(coord on = 0.0, Vertex v = {0.0, 0.0}) const override;
		void render(void) const override;

        bool isConcave(void) const;
        bool isConcave(const ConvexHull& v) const;
        void simplify(void);
};
COMMON_VERIFY(Polygon);

#endif /* POLYGON_H */

