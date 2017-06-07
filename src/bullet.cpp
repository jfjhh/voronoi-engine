#include "bullet.h"

void Bullet::render(double xoff, double yoff) const
{
	/* Render the bullet's texture. */
	texture->render(x, y);

	/* Render the bullet's hitbox. */
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xff, 0xff);
	Hitbox h = hitbox;
	h.offset(x, y);
	h.render();
}

void Bullet::setType(BulletType t)
{
	for (size_t i = 0; i < BULLETS_LENGTH; i++) {
		if (BULLETS[i].type == t) {
			texture = BULLETS[i].texture;
			hitbox  = BULLETS[i].hitbox;
		}
	}
}

BulletType Bullet::getType(void) const
{
	return type;
}

