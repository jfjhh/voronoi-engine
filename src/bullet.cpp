#include "bullet.h"

void Bullet::render(double xoff, double yoff) const
{
	// Render the bullet's texture.
	texture->render(x, y);

	// Render the bullet's hitbox.
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xff, 0xff);
	Hitbox h = hitbox;
	h.translate(x, y);
	h.render();
}

void Bullet::setType(BulletType t)
{
	for (const auto& b: BULLETS) {
		if (b.type == t) {
			texture = b.texture;
			hitbox  = b.hitbox;
		}
	}
}

BulletType Bullet::getType(void) const
{
	return type;
}

