/**
 * Shape Class.
 */

#ifndef SHAPE_H
#define SHAPE_H

#include <memory>
#include <algorithm>
#include <vector>
#include "vertex.h"
#include "pob.h"

class Shape;
typedef std::shared_ptr<Shape>            ShapePointer;
typedef std::shared_ptr<Vertex>           VertexPointer;
typedef std::shared_ptr<VoronoiVertex>    VoronoiVertexPointer;
typedef std::vector<VertexPointer>        ConvexHull;
typedef std::vector<VoronoiVertexPointer> VoronoiHull;

class Shape
{
	protected:
		/**
		 * The shape's center.
		 */
		VoronoiVertex center;

		/**
		 * Vertex hulls.
		 */
		ConvexHull  chull;
		VoronoiHull vhull;

	public:
		/**
		 * Checks if the target shape intersects this one.
		 */
		virtual bool intersects(ShapePointer t) const = 0;

		/**
		 * Offsets the shape's position.
		 *
		 * Often used to translate a shape from the origin to somewhere in the
		 * plane.
		 */
		virtual void offset(double x, double y);

		/**
		 * Renders the shape on the screen.
		 */
		virtual void render(void) const = 0;

		/**
		 * Getters.
		 */
		VoronoiVertex getCenter(void) const;
		double getCenterX(void) const;
		double getCenterY(void) const;
		double getVoronoiRadius(void) const;

		virtual ConvexHull  getVertices(void) const;
		virtual VoronoiHull getVoronoiVertices(void) const;
};

#endif /* SHAPE_H */

