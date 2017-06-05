/**
 * PObject Class.
 * Alex Striff.
 */

#ifndef POBJECT_H
#define POBJECT_H

#include <math.h>
#include <vector>
#include "pob.h"
#include "ptexture.h"
#include "hitbox.h"

class PObject
{
	protected:
		/**
		 * Game display and logic variables.
		 */
		PTexture texture;
		Hitbox   hitbox;

		/**
		 * Physics variables.
		 *
		 * x     : x position.
		 * y     : y position.
		 * t     : angle (theta).
		 * v     : linear velocity (magnitude).
		 * w     : angular velocity.
		 * a     : linear acceleration.
		 * aa    : angular acceleration.
		 * vmax  : maximum linear velocity.
		 * wmax  : maximum angular velocity.
		 * amax  : maximum linear acceleration.
		 * aamax : maximum angular acceleration.
		 */
		double x, y, t, v, w, a, aa, vmax, wmax, amax, aamax;

	public:
		/**
		 * Initializes the object.
		 */
		PObject();
		
		/**
		 * Destroys the object.
		 */
		virtual ~PObject();

		/**
		 * Removes all object from the object.
		 */
		virtual void free(void);

		/**
		 * Updates the object's objects.
		 */
		virtual void update(float time);

		/**
		 * Renders the object's objects.
		 */
		virtual void render(float time);

		/**
		 * Gets an object's hitbox(es).
		 */
		virtual Hitbox getHitbox(void) const;
};

#endif /* POBJECT_H */


