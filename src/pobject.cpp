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

void PObject::offset(double dx, double dy)
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
	h.offset(x, y);
	return h;
}

void PObject::start(void)
{
	timer.start();
}

void PObject::stop(void)
{
	timer.stop();
}

void PObject::pause(void)
{
	timer.pause();
}

void PObject::unpause(void)
{
	timer.unpause();
}

double PObject::getTime(void) const
{
	return timer.ticks() / 1e3;
}

bool PObject::isStarted(void) const
{
	return timer.isStarted();
}

bool PObject::isPaused(void) const
{
	return timer.isPaused();
}

