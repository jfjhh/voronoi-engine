/**
 * Union Shape Class.
 */

#ifndef UNIONSHAPE_H
#define UNIONSHAPE_H

#include "pobt.h"
#include "shape.h"

using ShapeUnion = std::vector<ShapePointer>;

class UnionShape : virtual public Shape
{
	protected:
		ShapeUnion shapes;

	public:
		UnionShape(const UnionShape& p) = default;
		UnionShape& operator=(const UnionShape& p) = default;

		UnionShape(UnionShape&& p)
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
		void offset(double x, double y) final override;
		bool intersects(const Shape& t) const override;
		Range project(coord on = 0.0) const final override;
		void setAngle(double to) final override;

		ShapeUnion shapePointers(void) const;
};
POBT_VERIFY(UnionShape);

#endif /* UNIONSHAPE_H */


