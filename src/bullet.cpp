#include "bullet.h"

void Bullet::render(double xoff, double yoff) const
{
	// Render the bullet's texture.
	if (texture) {
		if (parent) {
			texture->render(
                    x + parent->transX() + xoff,
                    y + parent->transY() + yoff,
                    t);
		} else {
			texture->render(x + xoff, y + yoff, t);
		}
	}

	// Render the bullet's shape.
	// if (shape && !texture) {
	if (shape) {
		if (parent) {
			shape->renderTexture(
                    x + parent->transX() + xoff,
                    y + parent->transY() + yoff,
                    t);
		} else {
			shape->renderTexture(x + xoff, y + yoff, t);
		}
	}
}

void Bullet::setType(BulletType t)
{
	for (const auto& b: BULLETS) {
		if (b.type == t) {
			texture = b.texture;
			shape   = b.shape;
			return;
		}
	}
}

BulletType Bullet::getType(void) const
{
	return type;
}

