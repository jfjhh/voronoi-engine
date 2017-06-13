/**
 * Player Class.
 * Alex Striff.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"
#include "ptexture.h"
#include "shape.h"
#include "circle.h"

class Player
{
	protected:
		double x, y;
		int    vx, vy;
		bool   focused;
		int    xmotion, ymotion;
		bool   up_last, left_last, up, down, left, right;
		static std::shared_ptr<Shape> shape;

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
			}

		explicit Player(Player& p)    = delete;
		Player& operator=(Player& p)  = delete;
		explicit Player(Player&& p)   = default;
		Player& operator=(Player&& p) = default;

		~Player();

		void   handleEvent(const SDL_Event &e);
		void   move(double time);
		void   render(void);
		double angleFrom(double xf, double yf) const;
		Shape& objectShape(void) const;
		double getX(void) const;
		double getY(void) const;
		void   setPosition(double px, double py);
};
// COMMON_VERIFY_MOVE(Player);

#endif /* PLAYER_H */


