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
	d->translate(x, y);
	objects.push_back(d);
}

void Danmaku::update(void)
{
	PObject::update();
	for (auto it = objects.begin(); it != objects.end(); it++) {
		(*it)->update();
	}

	auto it = std::remove_if(objects.begin(), objects.end(),
			[](std::shared_ptr<PObject> o)
			{
			SDL_Rect field = {
			0,            0,
			(int) SCREEN_WIDTH, (int) SCREEN_HEIGHT,
			};
			Hitbox f;
			f.add(field);
			return !f.intersects(o->getHitbox());
			});
	objects.erase(it, objects.end());
}

void Danmaku::render(double xoff, double yoff) const
{
	// Render the danmaku's texture.
	if (texture != nullptr) {
		texture->render(
				x + xoff - (texture->swidth()  / 2),
				y + yoff - (texture->sheight() / 2));
	}

	// Render the danmaku's hitbox.
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0xff, 0xff, 0xff);
	Hitbox h = hitbox;
	h.translate(x + xoff, y + yoff);
	h.render();

	// Render the danmaku's objects.
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->render(x + xoff, y + yoff);
	}
}

void Danmaku::translate(double dx, double dy)
{
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->translate(dx, dy);
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

