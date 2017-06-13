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
		Rectangle(coord w,  coord h,
				coord x = 0.0,  coord y = 0.0, coord t = 0.0);

		Rectangle(coord w = 1.0): Rectangle(w, w, 0.0, 0.0, 0.0) {};

		Rectangle(const Rectangle& p) = default;
		Rectangle& operator=(const Rectangle& p) = default;

		operator SDL_Rect();

		bool intersects(const Shape& s) const final override;
		bool intersects(const VoronoiVertex& v) const;
		void render(void) const override;

		coord width(void)   const;
		coord height(void)  const;
		coord hwidth(void)  const;
		coord hheight(void) const;
};
COMMON_VERIFY(Rectangle);

#endif /* RECTANGLE_H */

