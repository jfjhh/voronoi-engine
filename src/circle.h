/**
 * A Circle Structure.
 * Alex Striff.
 */

#ifndef CIRCLE_H
#define CIRCLE_H

#include "pob.h"

typedef struct circle_t {
	int x, y, r;
} Circle;

/**
 * Check if a circle intersects with another shape.
 */
bool Circle_HasIntersection(const Circle *a, const Circle *b);
bool Circle_HasIntersection(const Circle *a, const SDL_Rect *b);

#endif /* CIRCLE_H */

