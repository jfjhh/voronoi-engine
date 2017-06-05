/**
 * Compound Hitbox Class.
 * Alex Striff.
 */

#ifndef HITBOX_H
#define HITBOX_H

#include <vector>

#include "pob.h"
#include "circle.h"

class Hitbox
{
	private:
		std::vector<SDL_Rect> rects;
		std::vector<Circle>   circles;
	
	public:
		/**
		 * Initializes the hitbox.
		 */
		/* Hitbox(); */

		/**
		 * Adds a rectangle to the hitbox.
		 */
		void addRect(SDL_Rect rect);

		/**
		 * Adds a circle to the hitbox.
		 */
		void addCircle(Circle circle);

		/**
		 * Checks intersection.
		 */
		bool intersects(Hitbox h) const;
		bool intersects(const SDL_Rect &r) const;
		bool intersects(const Circle &c) const;

		/**
		 * Computes the union rectangle of rects.
		 */
		SDL_Rect unionRect(void) const;
};

#endif /* HITBOX_H */

