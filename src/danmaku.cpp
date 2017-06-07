#include "danmaku.h"

Danmaku::~Danmaku()
{
	free();
}

void Danmaku::free(void)
{
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->free();
		objects[i].reset();
	}
	objects.clear();
}

void Danmaku::addPObject(std::shared_ptr<PObject> d)
{
	d->offset(x, y);
	objects.push_back(d);
}

void Danmaku::update(void)
{
	PObject::update();
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->update();
	}
}

void Danmaku::render(double xoff, double yoff) const
{
	/* Render the danmaku's texture. */
	texture.render(
			x + xoff - (texture.getSWidth()  / 2),
			y + yoff - (texture.getSHeight() / 2));

	/* Render the danmaku's hitbox. */
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0xff, 0xff, 0xff);
	Hitbox h = hitbox;
	h.offset(x + xoff, y + yoff);
	h.render();

	/* Render the danmaku's objects. */
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->render(x + xoff, y + yoff);
	}
}

void Danmaku::offset(double dx, double dy)
{
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->offset(dx, dy);
	}
}

void Danmaku::map(std::function<void(std::shared_ptr<PObject>,
			std::shared_ptr<Danmaku>, size_t)> f)
{
	for (size_t i = 0; i < objects.size(); i++) {
		f(objects[i], std::dynamic_pointer_cast<Danmaku>(objects[i]), i);
	}
}

Hitbox Danmaku::getHitbox(void) const
{
	Hitbox u;
	u.add(PObject::getHitbox());
	for (size_t i = 0; i < objects.size(); i++) {
		u.add(objects[i]->getHitbox());
	}
	return u;
}

void Danmaku::start(void)
{
	PObject::start();
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->start();
	}
}

void Danmaku::stop(void)
{
	PObject::stop();
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->stop();
	}
}

void Danmaku::pause(void)
{
	PObject::pause();
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->pause();
	}
}

void Danmaku::unpause(void)
{
	PObject::unpause();
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->unpause();
	}
}

