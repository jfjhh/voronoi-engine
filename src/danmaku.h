/**
 * Danmaku Class.
 * Alex Striff.
 */

#ifndef DANMAKU_H
#define DANMAKU_H

#include <functional>
#include <memory>
#include <vector>
#include "pobject.h"

class Danmaku : public PObject
{
	public:
		std::vector<std::shared_ptr<PObject>> objects;
		Danmaku(double x     = SCREEN_WIDTH  / 2,
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
				shape = std::make_shared<UnionShape>();
			}

		/**
		 * Destroys the danmaku.
		 */
		virtual ~Danmaku();

		/**
		 * Frees the danmaku.
		 */
		virtual void free(void) override;

		/**
		 * Adds an object to the danmaku.
		 */
		void addPObject(std::shared_ptr<PObject> d);

		/**
		 * Updates the danmaku's objects.
		 */
		virtual void update(void) override;

		/**
		 * Checks if a shape intersects the bullets in the danmaku.
		 */
		virtual bool intersects(const Shape& s) const override;

		/**
		 * Renders the danmaku's objects.
		 */
		virtual void render(double xoff = 0, double yoff = 0) const override;

		/**
		 * Offsets an object's position.
		 */
		// virtual void translate(double dx, double dy);

		/**
		 * Maps a function over a danmaku's objects.
		 */
		void map(std::function<void(std::shared_ptr<PObject>,
					std::shared_ptr<Danmaku>, size_t)> f);
};

#endif /* DANMAKU_H */

