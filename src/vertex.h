/**
 * Vertex Structure.
 */

#ifndef VERTEX_H
#define VERTEX_H

struct Vertex
{
	double x; /**< The x position of the vertex. */
	double y; /**< The y position of the vertex. */
	Vertex(double x = 0, double y = 0): x(x), y(y) {}
	void offset(double xoff, double yoff)
	{
		x += xoff;
		y += xoff;
	};
	double distanceTo(const Vertex t)
	{
		double dx = x - t.x;
		double dy = y - t.y;
		return sqrt(dx*dx + dy*dy);
	};
};

struct VoronoiVertex : Vertex
{
	double x; /**< The x position of the vertex. */
	double y; /**< The y position of the vertex. */
	double r; /**< The voronoi approximation radius of the vertex. */
	VoronoiVertex(double x = 0, double y = 0, double r = 0): x(x), y(y), r(r) {}
	double voronoiDistanceTo(const Vertex t)
	{
		return std::max(distanceTo(t) - r, 0.0);
	};
};

#endif /* VERTEX_H */

