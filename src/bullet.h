/**
 * Bullet Class.
 * Alex Striff.
 */

#ifndef BULLET_H
#define BULLET_H

#include <math.h>
#include <vector>
#include "common.h"
#include "pobject.h"
#include "bulletdata.h"

class Bullet : public PObject
{
	public:
		/**
		 * A bullet can be constructed just like an object.
		 */
		Bullet(
				double x     = SCREEN_WIDTH  / 2,
				double y     = SCREEN_HEIGHT / 2,
				double t     = 0,
				double v     = 0,
				double w     = 0,
				double a     = 0,
				double aa    = 0,
				bool   die   = true,
				double vmax  = 1e6,
				double wmax  = 1e6,
				double amax  = 1e6,
				double aamax = 1e6,
				double ttl   = 1e6):
			PObject(x, y, t, v, w, a, aa, die, vmax, wmax, amax, aamax, ttl) {
				setType(BulletType::NONE);
			};

		/**
		 * Renders the bullet.
		 */
		void render(double xoff = 0, double yoff = 0) const override;

		/**
		 * Set the bullet type.
		 */
		void setType(BulletType t);

		/**
		 * Get the bullet type.
		 */
		BulletType getType(void) const;

	protected:
		BulletType type;
};

#endif /* BULLET_H */

