#include "pobject.h"

PObject::~PObject()
{
	free();
}

void PObject::free(void)
{
	// Not needed because the texture is a reference.
	// texture->free();
}

void PObject::update(void)
{
	// Get time.
	double time = getTime();

	// Update linear velocity.
	v += a  * time;
	v  = std::max(std::min(v, vmax), -vmax);

	// Update angular velocity.
	w += aa * time;
	w  = std::max(std::min(w, wmax), -wmax);

	// Update angle.
	t += w * time;

	// Update x position.
	x += v * cos(t) * time;

	// Update y position.
	y += v * sin(t) * time;
}

void PObject::translate(double dx, double dy)
{
	x += dx;
	y += dy;
}

void PObject::setHitbox(Hitbox h)
{
	hitbox = h;
}

Hitbox PObject::getHitbox(void) const
{
	Hitbox h = hitbox;
	h.translate(x, y);
	return h;
}

double PObject::getTime(void) const
{
	return 1.0 / gFPS;
}

