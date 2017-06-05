/**
 * Danmaku Class.
 * Alex Striff.
 */

#ifndef DANMAKU_H
#define DANMAKU_H

#include <vector>
#include "pobject.h"

class Danmaku : public PObject
{
	private:
		std::vector<PObject> objects;

	public:
		/**
		 * Initializes the danmaku.
		 */
		Danmaku();
		
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
		void addPObject(PObject &o);

		/**
		 * Updates the danmaku's objects.
		 */
		virtual void update(float time) override;

		/**
		 * Renders the danmaku's objects.
		 */
		virtual void render(float time) override;

		/**
		 * Gets the union hitbox of the danmaku's hitboxes.
		 */
		virtual Hitbox getHitbox(void) const override;
};

#endif /* DANMAKU_H */

