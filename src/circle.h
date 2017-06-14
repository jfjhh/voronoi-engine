/**
 * Circle Class.
 * Alex Striff.
 */

#ifndef CIRCLE_H
#define CIRCLE_H

#include "common.h"
#include "ellipse.h"

class Circle : public Ellipse
{
	public:
		// For backwards-compatibility with an old Circle structure that
		// mirrored SDL_Rect. Remove these members when the Hitbox => Shape
		// migration is complete.
		// int x, y, r;

		Circle(coord x, coord y, coord r);
		Circle(coord r): Circle(0.0, 0.0, r) {};

		bool intersects(const Circle& s) const;
		void render(void) const final override;
		Range project(coord on, Vertex v = {0.0, 0.0}) const final override;

		// Circles are invariant under rotation, so do not waste time with
		// rotating them.
		void setAngle(coord to) final override {};

		coord radius(void) const;
};
COMMON_VERIFY(Circle);

#endif /* CIRCLE_H */

