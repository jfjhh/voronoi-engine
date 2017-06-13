#include "pobject.h"

PObject::~PObject()
{
	free();
}

void PObject::free(void)
{
	// Not needed because the texture is a std::shared_ptr.
	// texture->free();
}

void PObject::update(void)
{
	// Get time.
	auto time = gTimeStep;

	// Update linear velocity.
	v += a  * time;
	v  = std::max(std::min(v, vmax), -vmax);

	// Update angular velocity.
	w += aa * time;
	w  = std::max(std::min(w, wmax), -wmax);

	// Update angle.
	t += w * time;

	auto xo = 0.0;
	auto yo = 0.0;
	if (parent != nullptr) {
		xo = x;
		yo = y;
		x = 0;
		y = 0;
		// x = parent->transX();
		// y = parent->transY();
	}

	// Update x position.
	x += v * cos(t) * time;

	// Update y position.
	y += v * sin(t) * time;

	x += xo;
	y += yo;
}

bool PObject::intersects(const Shape& s) const
{
	return shape->intersects(s);
}

double PObject::transX(void) const
{
	return (parent == nullptr ? x : x + parent->transX());
}
double PObject::transY(void) const
{
	return (parent == nullptr ? y : y + parent->transY());
}

VoronoiVertex PObject::vpos(void) const
{
	return { x, y, shape->vcenter().r };
}

