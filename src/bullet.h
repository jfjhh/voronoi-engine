/**
 * Bullet Class.
 * Alex Striff.
 */

#ifndef BULLET_H
#define BULLET_H

#include <math.h>
#include <vector>
#include "pob.h"
#include "pobject.h"
#include "bulletdata.h"

class Bullet : public PObject
{
	public:
		/**
		 * A bullet can be constructed just like an object.
		 */
		using PObject::PObject;

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

