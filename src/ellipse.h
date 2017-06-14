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
		Ellipse(coord rx, coord ry,
				coord x  = 0.0,  coord y = 0.0, coord t = 0.0);

		Ellipse(const Ellipse& p) = default;
		Ellipse& operator=(const Ellipse& p) = default;

		bool intersects(const Shape& s) const final override;
		bool intersects(const Point& s) const;
		void render(void) const override;

		Range project(coord on = 0.0, Vertex v = {0.0, 0.0}) const override;

		coord xRadius(void) const;
		coord yRadius(void) const;
};
COMMON_VERIFY(Ellipse);

#endif /* ELLIPSE_H */

