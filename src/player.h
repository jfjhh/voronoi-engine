/**
 * Player Class.
 * Alex Striff.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "pob.h"
#include "ptexture.h"

class Player
{
	protected:
		/**
		 * The offsets of the player's position.
		 */
		int x, y;

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

	public:
		/**
		 * The maximum velocity of the player.
		 */
		static const int VELOCITY  = 8;

		/**
		 * The focused velocity divisor. Must be a divisor of VELOCITY.
		 */
		static const int FVELOCITY = 2;

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
			x(0),
			y(0),
			vx(0),
			vy(0),
			focused(false),
			xmotion(0),
			ymotion(0) {
				sprite.load(sprite_filename);
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
		void move(void);

		/**
		 * Renders the player.
		 */
		void render(void) const;
};

#endif /* PLAYER_H */


