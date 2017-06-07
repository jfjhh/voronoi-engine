#include "spellcard.h"

Spellcard::~Spellcard()
{
	free();
}

void Spellcard::free(void)
{
	for (size_t i = 0; i < danmaku.size(); i++) {
		danmaku[i].free();
	}
	danmaku.clear();
}

void Spellcard::addDanmaku(Danmaku d)
{
	danmaku.push_back(d);
}

void Spellcard::update(void)
{
	for (size_t i = 0; i < danmaku.size(); i++) {
		danmaku[i].update();
	}
}

void Spellcard::render(void)
{
	for (size_t i = 0; i < danmaku.size(); i++) {
		danmaku[i].render();
	}
}

Hitbox Spellcard::getHitbox(void) const
{
	Hitbox u;
	for (size_t i = 0; i < danmaku.size(); i++) {
		u.add(danmaku[i].getHitbox());
	}
	return u;
}

