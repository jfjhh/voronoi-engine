#include "bullet.h"

void Bullet::render(double xoff, double yoff) const
{
	// Render the bullet's texture.
	if (texture) {
		if (parent) {
			texture->render(x + parent->transX(), y + parent->transY());
		} else {
			texture->render(x, y);
		}
	}

	// Render the bullet's shape.
	if (shape && !texture) {
		if (parent) {
			shape->renderTexture(x + parent->transX(), y + parent->transY());
		} else {
			shape->renderTexture(x, y);
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

