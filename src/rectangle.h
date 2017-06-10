/**
 * Rectangle Class.
 * Alex Striff.
 */

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "point.h"

class Rectangle : virtual public Shape
{
	protected:
		// If speed becomes an issue, a slight speed up may be possible if
		// vertices like (x - hw, y - hw) are stored as class members.
		coord w, h, hw, hh;

	public:
		Rectangle(coord w = 1.0,  coord h = 1.0,
				coord x   = 0.0,  coord y = 0.0, coord t = 0.0);

		Rectangle(coord w = 1.0, coord x = 0.0,  coord y = 0.0, coord t = 0.0)
		{ Rectangle(w, w, x, y, t); }

		Rectangle(const Rectangle& p) = default;
		Rectangle& operator=(const Rectangle& p) = default;

		Rectangle(Rectangle&& p)
		{
			chull  = std::move(p.vertices());
			vhull  = std::move(p.voronoiVertices());
			center = p.vcenter();
			t      = p.angle();
			w      = p.width();
			h      = p.height();
		}
		Rectangle& operator=(Rectangle&& p)
		{
			chull  = std::move(p.vertices());
			vhull  = std::move(p.voronoiVertices());
			center = p.vcenter();
			t      = p.angle();
			w      = p.width();
			h      = p.height();
			return *this;
		}

		bool intersects(const Shape& s) const final override;
		void render(void) const override;

		coord width(void)   const;
		coord height(void)  const;
		coord hwidth(void)  const;
		coord hheight(void) const;
};
POBT_VERIFY_BASIC(Rectangle);

#endif /* RECTANGLE_H */

