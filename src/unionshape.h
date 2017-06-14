/**
 * Union Shape Class.
 */

#ifndef UNIONSHAPE_H
#define UNIONSHAPE_H

#include "commont.h"
#include "shape.h"

using ShapeUnion = std::vector<ShapePointer>;

class UnionShape : virtual public Shape
{
	protected:
		ShapeUnion shapes;

		void updateTextureSide(void);

	public:
		UnionShape(): Shape() {};

		UnionShape(const UnionShape& p) = default;
		UnionShape& operator=(const UnionShape& p) = default;

		UnionShape(UnionShape&& p):
			Shape()
		{
			shapes = std::move(p.shapePointers());
			chull  = std::move(p.vertices());
			vhull  = std::move(p.voronoiVertices());
			center = p.vcenter();
			t      = p.angle();
		}
		UnionShape& operator=(UnionShape&& p)
		{
			shapes = std::move(p.shapePointers());
			chull  = std::move(p.vertices());
			vhull  = std::move(p.voronoiVertices());
			center = p.vcenter();
			t      = p.angle();
			return *this;
		}

		void add(ShapePointer t);

		void render(void) const override;
		void translate(double x, double y) final override;
		bool intersects(const Shape& t) const override;
		Range project(coord on = 0.0, Vertex v = {0.0, 0.0}) const override;
		void setAngle(double to) final override;
		void rotate(double by) final override;

		ShapeUnion shapePointers(void) const;
};
COMMON_VERIFY(UnionShape);

#endif /* UNIONSHAPE_H */


