/**
 * A Ellipse Class.
 * Alex Striff.
 */

#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "point.h"

class Ellipse : virtual public Shape
{
	protected:
		coord rx, ry;

	public:
		Ellipse(coord rx = 1.0, coord ry = 1.0,
				coord x  = 0.0,  coord y = 0.0, coord t = 0.0);

		Ellipse(const Ellipse& p) = default;
		Ellipse& operator=(const Ellipse& p) = default;

		Ellipse(Ellipse&& p)
		{
			chull  = std::move(p.vertices());
			vhull  = std::move(p.voronoiVertices());
			center = p.vcenter();
			t      = p.angle();
			rx     = p.xRadius();
			ry     = p.yRadius();
		}
		Ellipse& operator=(Ellipse&& p)
		{
			chull  = std::move(p.vertices());
			vhull  = std::move(p.voronoiVertices());
			center = p.vcenter();
			t      = p.angle();
			rx     = p.xRadius();
			ry     = p.yRadius();
			return *this;
		}

		bool intersects(const Shape& t) const final override;
		bool intersects(const Point& t) const;
		void render(void) const override;

		Range project(coord on = 0.0) const override;

		coord xRadius(void) const;
		coord yRadius(void) const;
};
COMMON_VERIFY(Ellipse);

#endif /* ELLIPSE_H */

