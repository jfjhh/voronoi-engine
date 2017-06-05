/**
 * Spell Card Class.
 * Alex Striff.
 */

#ifndef SPELLCARD_H
#define SPELLCARD_H

#include <vector>
#include "danmaku.h"

class Spellcard
{
	private:
		std::vector<Danmaku> danmaku;

	public:
		/**
		 * Initializes the spell card.
		 */
		Spellcard();
		
		/**
		 * Destroys the spell card.
		 */
		~Spellcard();

		/**
		 * Removes all danmaku from the spell card.
		 */
		void free(void);

		/**
		 * Adds a danmaku to the spell card.
		 */
		void addDanmaku(Danmaku &d);

		/**
		 * Updates the spell card's danmaku.
		 */
		void update(float time);

		/**
		 * Renders the spell card's danmaku.
		 */
		void render(float time);

		/**
		 * Gets the union hitbox of the danmaku hitboxes.
		 */
		Hitbox getHitbox(void) const;
};

#endif /* SPELLCARD_H */

