/**
 * A Circle Structure.
 * Alex Striff.
 */

#ifndef CIRCLE_H
#define CIRCLE_H

#include "pob.h"

struct Circle
{
	int x;
	int y;
	int r;
};

/**
 * Check if a circle intersects with another shape.
 */
bool Circle_HasIntersection(const Circle *a, const Circle *b);
bool Circle_HasIntersection(const Circle *a, const SDL_Rect *b);

#endif /* CIRCLE_H */

