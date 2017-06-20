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
					SCREEN_WIDTH,     SCREEN_HEIGHT,
					SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		};

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

		virtual bool intersects(const Shape& ps) const override;

		/**
		 * Renders the stage's objects.
		 */
		virtual void render(double xoff = 0, double yoff = 0) const override;

		/**
		 * Maps a function over a stage's objects.
		 */
		void map(std::function<void(std::shared_ptr<PObject>,
					std::shared_ptr<Stage>, size_t)> f);

        VoronoiHull voronoiVertices(void) const;
        VoronoiHull voronoiVertices(coord x, coord y, coord range) const;
};

#endif /* STAGE_H */

