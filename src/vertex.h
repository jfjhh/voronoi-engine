/**
 * Vertex Structure.
 */

#ifndef VERTEX_H
#define VERTEX_H

#include "commont.h"
#include "range.h"

struct VoronoiVertex;

struct Vertex
{
	coord x; /**< The x position of the vertex. */
	coord y; /**< The y position of the vertex. */

	Vertex(coord x = 0.0, coord y = 0.0):
		x(x), y(y) {}

	operator VoronoiVertex(void) const;

	void translate(coord xoff, coord yoff)
	{
		x += xoff;
		y += xoff;
	};
	void translate(const Vertex& v)
	{
		translate(v.x, v.y);
	};

	const Vertex operator-(void) const
	{
		return Vertex{-x, -y};
	};

	Vertex& operator+=(const Vertex& v)
	{
		translate(v);
		return *this;
	};
	const Vertex operator+(const Vertex& v) const
	{
		return Vertex(*this) += v;
	};

	Vertex& operator-=(const Vertex& v)
	{
		*this += -v;
		return *this;
	};
	const Vertex operator-(const Vertex& v) const
	{
		return Vertex(*this) -= v;
	};

	coord distanceTo(const Vertex& t = { 0.0, 0.0 }) const
	{
		auto dx = x - t.x;
		auto dy = y - t.y;
		return sqrt(dx*dx + dy*dy);
	};

	Vertex rotate(coord to, coord ox = 0.0, coord oy = 0.0) const
	{
		auto c = cos(to);
		auto s = sin(to);
		return Vertex{
			(((x - ox) * c) - ((y - oy) * s)) + ox,
			(((y - oy) * s) + ((y - oy) * c)) + oy
		};
	};
};
COMMON_VERIFY(Vertex);

struct VoronoiVertex : Vertex
{
	coord x; /**< The x position of the vertex. */
	coord y; /**< The y position of the vertex. */
	coord r; /**< The voronoi approximation radius of the vertex. */

	VoronoiVertex(coord x = 0.0, coord y = 0.0, coord r = 0.0):
		x(x), y(y), r(r) {}

	VoronoiVertex(const Vertex& v, coord r = 0.0):
		x(v.x), y(v.y), r(r) {}
	VoronoiVertex(Vertex&& v, coord r = 0.0):
		x(std::move(v.x)), y(std::move(v.y)), r(r) {}

	const VoronoiVertex operator-(void) const
	{
		return VoronoiVertex{-x, -y, r};
	};

	VoronoiVertex& operator+=(const VoronoiVertex& v)
	{
		translate(v);
		r = std::max(r, v.r);
		return *this;
	};
	const VoronoiVertex operator+(const VoronoiVertex& v) const
	{
		return VoronoiVertex(*this) += v;
	};

	VoronoiVertex& operator-=(const VoronoiVertex& v)
	{
		*this += -v;
		return *this;
	};
	const VoronoiVertex operator-(const VoronoiVertex& v) const
	{
		return VoronoiVertex(*this) -= v;
	};

	coord voronoiDistanceTo(const Vertex& t = { 0.0, 0.0 }) const
	{
		return std::max(distanceTo(t) - r, 0.0);
	};

	VoronoiVertex rotate(coord to, coord ox = 0.0, coord oy = 0.0) const
	{
		return { std::move(Vertex::rotate(to, ox, oy)), r };
	};
};
COMMON_VERIFY(VoronoiVertex);

inline Vertex::operator VoronoiVertex(void) const
{
	return VoronoiVertex{*this};
}

#endif /* VERTEX_H */

