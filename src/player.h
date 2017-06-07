/**
 * Player Class.
 * Alex Striff.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "pob.h"
#include "ptexture.h"
#include "hitbox.h"

class Player
{
	protected:
		/**
		 * The offsets of the player's position.
		 */
		double x, y;

		/**
		 * The velocities of the player.
		 */
		int vx, vy;

		/**
		 * The focus state of the player.
		 */
		bool focused;

		/**
		 * Keys pressed for motion along an axis.
		 */
		int  xmotion, ymotion;
		bool up_last, left_last, up, down, left, right;

		/**
		 * Player hitbox.
		 */
		Hitbox hitbox;

	public:
		/**
		 * The maximum velocity of the player.
		 */
		static const int VELOCITY = 500;

		/**
		 * The focused velocity divisor.
		 */
		static constexpr double FVELOCITY = 3;

		/**
		 * The sprite enum.
		 */
		enum Sprite : int {
			FOCUS = 3,
			ALL   = 0,
			LEFT,    CENTER,    RIGHT,
			F_LEFT,  F_CENTER,  F_RIGHT,
		};

		/**
		 * The player's sprite texture.
		 */
		PTexture sprite;

		/**
		 * Initializes the player.
		 */
		Player(std::string sprite_filename):
			x(SCREEN_WIDTH  / 2),
			y(SCREEN_HEIGHT / 2),
			vx(0),
			vy(0),
			focused(false),
			xmotion(0),
			ymotion(0) {
				sprite.load(sprite_filename);
				sprite.setSGrid(32, 32);

				Circle hit_circle = {0, 0, 5};
				hitbox.add(hit_circle);
			}

		/**
		 * Destroys the player.
		 */
		~Player();

		/**
		 * Handles motion events.
		 */
		void handleEvent(SDL_Event &e);

		/**
		 * Moves the player.
		 */
		void move(double time);

		/**
		 * Renders the player.
		 */
		void render(void) const;

		/**
		 * Gets the angle from a position to the player.
		 */
		double angleFrom(double xf, double yf) const;

		/**
		 * Gets the player's hitbox.
		 */
		Hitbox getHitbox(void) const;

		/**
		 * Gets the player's x position.
		 */
		double getX(void) const;

		/**
		 * Gets the player's y position.
		 */
		double getY(void) const;

		/**
		 * Sets the player's position.
		 */
		void setPosition(double px, double py);
};

#endif /* PLAYER_H */


