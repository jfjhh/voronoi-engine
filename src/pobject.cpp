#include "pobject.h"

PObject::~PObject()
{
	free();
}

void PObject::free(void)
{
	texture.free();
}

void PObject::update(float time)
{
	/* TODO: Update linear acceleration according to function. */
	/* TODO: Update angular acceleration according to function. */

	/* Update linear velocity. */
	v += a  * time;
	v  = std::max(std::min(v, vmax), 0.0);

	/* Update angular velocity. */
	w += aa * time;
	w  = std::max(std::min(w, wmax), 0.0);

	/* Update angle. */
	t += w;

	/* Update x position. */
	x  = v * cos(t) * time;

	/* Update y position. */
	y  = v * sin(t) * time;
}

void PObject::render(float time)
{
	texture.render(((int) x) + (texture.getSWidth() / 2),
			((int) y) + (texture.getSHeight() / 2));
}

Hitbox PObject::getHitbox(void) const
{
	return hitbox;
}

