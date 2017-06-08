/**
 * Union Shape Class.
 */

#ifndef UNIONSHAPE_H
#define UNIONSHAPE_H

#include "shape.h"

typedef std::vector<ShapePointer> ShapeUnion;

class UnionShape : virtual public Shape
{
	protected:
		/**
		 * The shape union's center.
		 */
		ShapeUnion shapes;

	public:
		/**
		 * Adds the shape to the union.
		 */
		void add(ShapePointer t);

		/**
		 * Offsets the shape's position.
		 *
		 * Often used to translate a shape from the origin to somewhere in the
		 * plane.
		 */
		void offset(double x, double y);

		/**
		 * Checks if the target shape intersects this one.
		 */
		bool intersects(ShapePointer t) const;

		/**
		 * Renders the shape on the screen.
		 */
		void render(void) const = 0;
};

#endif /* UNIONSHAPE_H */


