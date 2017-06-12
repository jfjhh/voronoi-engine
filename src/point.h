/**
 * Point Class.
 */

#ifndef POINT_H
#define POINT_H

#include "shape.h"

class Point : virtual public Shape
{
	public:
		Point(coord x, coord y);

		Point(const Point& p) = default;
		Point& operator=(const Point& p) = default;

		Point(Point&& p):
			Shape()
		{
			chull  = std::move(p.vertices());
			vhull  = std::move(p.voronoiVertices());
			center = p.vcenter();
			t      = p.angle();
		}
		Point& operator=(Point&& p)
		{
			chull  = std::move(p.vertices());
			vhull  = std::move(p.voronoiVertices());
			center = p.vcenter();
			t      = p.angle();
			return *this;
		}

		bool intersects(const Shape& t) const final override;
		bool intersects(const Point& t) const;
		void render(void) const final override;
};
COMMON_VERIFY(Point);

#endif /* POINT_H */

