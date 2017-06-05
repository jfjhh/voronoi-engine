#include "danmaku.h"

Danmaku::~Danmaku()
{
	free();
}

void Danmaku::free(void)
{
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i].free();
	}
	objects.clear();
}

void Danmaku::addPObject(PObject &d)
{
	objects.push_back(d);
}

void Danmaku::update(float time)
{
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i].update(time);
	}
}

void Danmaku::render(float time)
{
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i].render(time);
	}
}

Hitbox Danmaku::getHitbox(void) const
{
	Hitbox u;
	for (size_t i = 0; i < objects.size(); i++) {
		u.add(objects[i].getHitbox());
	}
	return u;
}

