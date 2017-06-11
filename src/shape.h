/**
 * Shape Class.
 */

#ifndef SHAPE_H
#define SHAPE_H

#include <algorithm>
#include <vector>
#include "vertex.h"
#include "range.h"
#include "common.h"

using ConvexHull  = std::vector<Vertex>;
using VoronoiHull = std::vector<VoronoiVertex>;

class Shape
{
	protected:
		ConvexHull    chull;
		VoronoiHull   vhull;
		VoronoiVertex center;
		coord t; /**< Angle of shape. */

	public:
		virtual void translate(coord x, coord y);
		virtual bool intersects(const Shape& t) const = 0;
		virtual void render(void) const = 0;

		virtual void setAngle(coord to);
		virtual void rotate(coord by);
		coord angle(void) const;

		virtual Range projectOn(coord axis = 0.0) const;
		virtual Range project(coord on = 0.0) const;

		VoronoiVertex vcenter(void) const;
		virtual ConvexHull  vertices(void) const;
		virtual VoronoiHull voronoiVertices(void) const;
};
COMMON_VERIFY_BASIC(Shape);

using ShapePointer = std::shared_ptr<Shape>;

#endif /* SHAPE_H */

