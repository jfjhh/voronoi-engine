#include "circle.h"

Circle::Circle(coord r, coord x, coord y):
	r((int)r), x((int)x), y((int)y)
{
	t      = 0.0;
	rx     = r;
	ry     = r;
	center = {x, y, rx};
	chull.push_back(center);
	vhull.push_back(center);
}

bool Circle::intersects(const Circle& t) const
{
	auto v = t.vcenter();

	// Check if the squared sum of the radii is greater than the
	// squared distance between centers.
	return pow(rx + v.r, 2)
		>  pow(center.x - v.x, 2) + pow(center.y - v.y, 2);
}

void Circle::render(void) const
{
	circleRGBA(gRenderer, center.x, center.y, rx, 255, 0, 255, 255);
}

coord Circle::radius(void) const
{
	return rx;
}

Range Circle::project(coord on) const
{
	auto c = center.distanceTo() * cos(on); // Project the center.
	return Range{c - rx, c + rx};
}

bool Circle_HasIntersection(const Circle *a, const Circle *b)
{
	// Squared distance between centers.
	int dx = a->x - b->x;
	int dy = a->y - b->y;
	int dd = dx*dx + dy*dy;

	// Sum of radii.
	int d  = a->r + b->r;

	return (dd < d*d);
}

bool Circle_HasIntersection(const Circle *a, const SDL_Rect *b)
{
	int cx, cy;

	// Closest box x to the circle.
	if (a->x < b->x) {
		cx = b->x;
	} else if (a->x > b->x + b->w) {
		cx = b->x + b->w;
	} else {
		cx = a->x;
	}

	// Closest box y to the circle.
	if (a->y < b->y) {
		cy = b->y;
	} else if (a->y > b->y + b->w) {
		cy = b->y + b->w;
	} else {
		cy = a->y;
	}

	// Check circumscribed square of circle collision with box.
	if (cx == a->x && cy == a->y) {
		return true;
	}

	// Check if closest point on box is less than a radius away.
	int dx = a->x - cx;
	int dy = a->y - cy;
	return (dx*dx + dy*dy < a->r*a->r);
}

