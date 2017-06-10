/**
 * Vertex Structure.
 */

#ifndef VERTEX_H
#define VERTEX_H

#include "pobt.h"
#include "range.h"

struct Vertex
{
	coord x; /**< The x position of the vertex. */
	coord y; /**< The y position of the vertex. */

	Vertex(coord x = 0.0, coord y = 0.0):
		x(x), y(y) {}

	void offset(coord xoff, coord yoff)
	{
		x += xoff;
		y += xoff;
	};

	coord distanceTo(const Vertex& t = { 0.0, 0.0 }) const
	{
		coord dx = x - t.x;
		coord dy = y - t.y;
		return sqrt(dx*dx + dy*dy);
	};
};
POBT_VERIFY(Vertex);

struct VoronoiVertex : Vertex
{
	coord x; /**< The x position of the vertex. */
	coord y; /**< The y position of the vertex. */
	coord r; /**< The voronoi approximation radius of the vertex. */

	VoronoiVertex(coord x = 0.0, coord y = 0.0, coord r = 0.0):
		x(x), y(y), r(r) {}

	coord voronoiDistanceTo(const Vertex& t = { 0.0, 0.0 }) const
	{
		return std::max(distanceTo(t) - r, 0.0);
	};
};
POBT_VERIFY(VoronoiVertex);

#endif /* VERTEX_H */

