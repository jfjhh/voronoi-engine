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
	public:
		std::vector<std::shared_ptr<PObject>> objects;
		Stage(): Danmaku() {
			shape = std::make_shared<Rectangle>(
					SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
					SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		};
		// Stage(double x     = SCREEN_WIDTH  / 2,
		// 		double y     = SCREEN_HEIGHT / 2,
		// 		double t     = 0,
		// 		double v     = 0,
		// 		double w     = 0,
		// 		double a     = 0,
		// 		double aa    = 0,
		// 		bool   die   = true,
		// 		double vmax  = 1e6,
		// 		double wmax  = 1e6,
		// 		double amax  = 1e6,
		// 		double aamax = 1e6,
		// 		double ttl   = 1e6):
		// 	PObject(x, y, t, v, w, a, aa, die, vmax, wmax, amax, aamax, ttl) {
		// 		shape = std::make_shared<UnionShape>();
		// 	}

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
};

#endif /* STAGE_H */

