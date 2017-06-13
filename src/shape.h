/**
 * Shape Class.
 */

#ifndef SHAPE_H
#define SHAPE_H

#include <memory>
#include <algorithm>
#include <vector>
#include "common.h"
#include "ptexture.h"
#include "range.h"
#include "vertex.h"

using ConvexHull  = std::vector<Vertex>;
using VoronoiHull = std::vector<VoronoiVertex>;

class Shape
{
	protected:
		std::shared_ptr<PTexture> shapeTexture;
		int             textureSide;
		bool            textureOK;
		ConvexHull      chull;
		VoronoiHull     vhull;
		VoronoiVertex   center;
		coord t; /**< Angle of shape. */

		void renderTargeted(void);

	public:
		Shape(coord tw = 0.0);
		Shape(coord tw, coord th);

		virtual void translate(coord x, coord y);
		virtual bool intersects(const Shape& t) const = 0;
		virtual void render(void) const;

		void renderTexture(coord x, coord y, coord add_rot = 0.0);
		void renderTexture(Vertex v) { renderTexture(v.x, v.y); };
		void renderTexture(coord add_rot = 0.0) { renderTexture(0.0, 0.0, add_rot); };
		bool setTextureWidth(int tw);
		bool renewTexture(void);
		bool textureStatus(void);

		virtual void setAngle(coord to);
		virtual void rotate(coord by);
		coord angle(void) const;

		virtual Range projectOn(coord axis = 0.0) const;
		virtual Range project(coord on = 0.0) const;

		virtual void setVCenter(const VoronoiVertex& v);
		VoronoiVertex vcenter(void) const;
		virtual ConvexHull  vertices(void) const;
		virtual VoronoiHull voronoiVertices(void) const;
};
COMMON_VERIFY_BASIC(Shape);

using ShapePointer = std::shared_ptr<Shape>;

#endif /* SHAPE_H */

