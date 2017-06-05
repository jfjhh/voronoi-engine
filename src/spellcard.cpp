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

void Spellcard::addDanmaku(Danmaku &d)
{
	danmaku.push_back(d);
}

void Spellcard::update(float time)
{
	for (size_t i = 0; i < danmaku.size(); i++) {
		danmaku[i].update(time);
	}
}

void Spellcard::render(float time)
{
	for (size_t i = 0; i < danmaku.size(); i++) {
		danmaku[i].render(time);
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

