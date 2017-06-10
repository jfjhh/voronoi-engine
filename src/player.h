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
		double x, y;
		int    vx, vy;
		bool   focused;
		int    xmotion, ymotion;
		bool   up_last, left_last, up, down, left, right;
		Hitbox hbox;

	public:
		enum Sprite : int {
			FOCUS = 3,
			ALL   = 0,
			LEFT,    CENTER,    RIGHT,
			F_LEFT,  F_CENTER,  F_RIGHT,
		};

		static constexpr double VELOCITY  = 500;
		static constexpr double FVELOCITY = 3; /**< Focused velocity divisor. */

		PTexture sprite;

		Player(const std::string& sprite_filename):
			x(SCREEN_WIDTH  / 2),
			y(SCREEN_HEIGHT / 2),
			vx(0),
			vy(0),
			focused(false),
			xmotion(0),
			ymotion(0) {
				sprite.load(sprite_filename);
				sprite.setGrid(32, 32);
				Circle hit_circle = {0, 0, 5};
				hbox.add(hit_circle);
			}
		Player(std::string&& sprite_filename):
			x(SCREEN_WIDTH  / 2),
			y(SCREEN_HEIGHT / 2),
			vx(0),
			vy(0),
			focused(false),
			xmotion(0),
			ymotion(0) {
				sprite.load(std::move(sprite_filename));
				sprite.setGrid(32, 32);
				Circle hit_circle = {0, 0, 5};
				hbox.add(hit_circle);
			}

		explicit Player(Player& p)    = delete;
		Player& operator=(Player& p)  = delete;
		explicit Player(Player&& p)   = default;
		Player& operator=(Player&& p) = default;

		~Player();

		void   handleEvent(const SDL_Event &e);
		void   move(double time);
		void   render(void) const;
		double angleFrom(double xf, double yf) const;
		Hitbox hitbox(void) const;
		double getX(void) const;
		double getY(void) const;
		void   setPosition(double px, double py);
};
POBT_VERIFY_MOVE(Player);

#endif /* PLAYER_H */


