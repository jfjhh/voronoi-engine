/**
 * Stage Class.
 * Alex Striff.
 *
 * TODO: Give each Stage it's own Player, or multiple players.
 */

#ifndef STAGE_H
#define STAGE_H

#include <functional>
#include <memory>
#include <vector>
#include "danmaku.h"
#include "bullet.h"
#include "player.h"

class Stage : public Danmaku
{
	private:
		std::vector<std::shared_ptr<PObject>> objects;

	public:
		/**
		 * A stage can be constructed just like an object.
		 */
		using PObject::PObject;

		/**
		 * Destroys the stage.
		 */
		virtual ~Stage();

		/**
		 * Frees the stage.
		 */
		virtual void free(void) override;

		/**
		 * Adds an object to the stage.
		 */
		void addPObject(std::shared_ptr<PObject> d);

		/**
		 * Updates the stage's objects.
		 */
		virtual void update(void) override;

		/**
		 * Renders the stage's objects.
		 */
		virtual void render(double xoff = 0, double yoff = 0) const override;

		/**
		 * Maps a function over a stage's objects.
		 */
		void map(std::function<void(std::shared_ptr<PObject>,
					std::shared_ptr<Stage>, size_t)> f);

		/**
		 * Timer actions.
		 */
		void start(void) override;
		void stop(void) override;
		void pause(void) override;
		void unpause(void) override;
};

#endif /* STAGE_H */

