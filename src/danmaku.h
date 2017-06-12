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
	private:
		std::vector<std::shared_ptr<PObject>> objects;

	public:
		/**
		 * A danmaku can be constructed just like an object.
		 */
		using PObject::PObject;

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
		 * Renders the danmaku's objects.
		 */
		virtual void render(double xoff = 0, double yoff = 0) const override;

		/**
		 * Offsets an object's position.
		 */
		virtual void translate(double dx, double dy);

		/**
		 * Maps a function over a danmaku's objects.
		 */
		void map(std::function<void(std::shared_ptr<PObject>,
					std::shared_ptr<Danmaku>, size_t)> f);

		/**
		 * Gets the union hitbox of the danmaku's hitboxes.
		 */
		virtual Hitbox getHitbox(void) const override;
};

#endif /* DANMAKU_H */

