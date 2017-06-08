/**
 * Compound Hitbox Class.
 * Alex Striff.
 */

#ifndef HITBOX_H
#define HITBOX_H

#include <algorithm>
#include <memory>
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
		Hitbox(std::vector<SDL_Rect> rx = std::vector<SDL_Rect>(),
				std::vector<Circle>  cx = std::vector<Circle>()):
			rects(rx),
			circles(cx) {}

		/**
		 * Adds a rectangle to the hitbox.
		 */
		void add(SDL_Rect rect);

		/**
		 * Adds a circle to the hitbox.
		 */
		void add(Circle circle);

		/**
		 * Adds the hitboxes elements to this hitbox.
		 */
		void add(const Hitbox h);

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

		/**
		 * Moves the hitbox to be centered around new coordinates.
		 */
		void offset(int x, int y);

		/**
		 * Renders the hitbox on screen.
		 */
		void render(void) const;

		/**
		 * Gets the hitboxes rectangle vector.
		 */
		std::vector<SDL_Rect> getRects(void) const;

		/**
		 * Gets the hitboxes circle vector.
		 */
		std::vector<Circle> getCircles(void) const;
};

#endif /* HITBOX_H */

