#include "vertex.h"

coord distance(const Vertex& t)
{
	return sqrt((t.x)*(t.x) + (t.y)*(t.y));
}

