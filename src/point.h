/**
 * Point Class.
 */

#ifndef POINT_H
#define POINT_H

#include "shape.h"

class Point : virtual public Shape
{
	public:
		/**
		 * Checks if the target shape intersects this one.
		 */
		bool intersects(ShapePointer t) const;

		/**
		 * Renders the shape on the screen.
		 */
		void render(void) const;
};

#endif /* POINT_H */


