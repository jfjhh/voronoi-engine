/**
 * PObject Class.
 * Alex Striff.
 */

#ifndef POBJECT_H
#define POBJECT_H

#include <math.h>
#include <memory>
#include <vector>
#include "common.h"
#include "ptexture.h"
#include "geometry.h"

#include "bulletdata.h" // DEBUG

class PObject
{
	public:
		/**
		 * Physics variables.
		 *
		 * x     : x position.
		 * y     : y position.
		 * t     : angle (theta).
		 * v     : linear velocity.
		 * w     : angular velocity.
		 * a     : linear acceleration.
		 * aa    : angular acceleration.
		 * vmax  : maximum linear velocity.
		 * wmax  : maximum angular velocity.
		 * amax  : maximum linear acceleration.
		 * aamax : maximum angular acceleration.
		 */
		double x, y, t, v, w, a, aa, vmax, wmax, amax, aamax;

		/**
		 * Control variables.
		 */
		bool     die;     /**< After ttl, should the object die or stop?    */
		double   ttl;     /**< How long until the object's motion stops.    */
		bool     hurt;    /**< Effect the player?                           */
		bool     just;    /**< Effect enemies?                              */

		std::shared_ptr<PObject> parent;
		std::shared_ptr<Shape>   shape;

		/**
		 * Initializes the object.
		 */
		PObject(double x     = SCREEN_WIDTH  / 2,
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
			x(x),
			y(y),
			t(t),
			v(v),
			w(w),
			a(a),
			aa(aa),
			vmax(vmax),
			wmax(wmax),
			amax(amax),
			aamax(aamax),
			die(die),
			ttl(ttl),
			hurt(true),
			just(false),
			parent(nullptr),
			shape(nullptr),
			texture(nullptr) {}

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
		virtual void update(void);

		/**
		 * Checks if a shape intersects the object.
		 */
		virtual bool intersects(const Shape& s) const;

		/**
		 * Renders the object's objects.
		 */
		virtual void render(double xoff = 0, double yoff = 0) const = 0;

		/**
		 * Offsets an object's position.
		 */
		virtual double transX(void) const;
		virtual double transY(void) const;

		virtual VoronoiVertex vpos(void) const;

	protected:
		/**
		 * Game display and logic variables.
		 */
		std::shared_ptr<PTexture> texture; /**< A pointer to the texture. */
};

#endif /* POBJECT_H */


