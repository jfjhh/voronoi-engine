#include "point.h"

bool Point::intersects(ShapePointer t) const
{
	return false;
}

void Point::render(void) const
{
	pixelRGBA(gRenderer, getCenterX(), getCenterY(), 255, 0, 255, 255);
}

