/**
 * Circle Class.
 * Alex Striff.
 */

#ifndef CIRCLE_H
#define CIRCLE_H

#include "pob.h"
#include "ellipse.h"

class Circle : public Ellipse
{
	public:
		// For backwards-compatibility with an old Circle structure that
		// mirrored SDL_Rect. Remove these members when the Hitbox => Shape
		// migration is complete.
		int r, x, y;

		Circle(coord r = 1.0, coord x = 1.0, coord y = 1.0);

		bool intersects(const Circle& t) const;
		void render(void) const final override;
		Range project(coord on) const final override;
		coord radius(void) const;
};
POBT_VERIFY_BASIC(Circle);

bool Circle_HasIntersection(const Circle *a, const Circle *b);
bool Circle_HasIntersection(const Circle *a, const SDL_Rect *b);

#endif /* CIRCLE_H */

