#include "player.h"

Player::~Player()
{
	sprite.free();
}

void Player::handleEvent(SDL_Event &e)
{
	/* Change velocities according to key directions. */
    if ((e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) && e.key.repeat == 0) {
		int direction = (e.type == SDL_KEYDOWN) ? 1 : -1;
		int velocity  = focused ? VELOCITY / FVELOCITY : VELOCITY;
		velocity     *= direction;
        switch (e.key.keysym.sym) {
            case SDLK_UP:
				vy -= velocity;
				break;
            case SDLK_DOWN:
				vy += velocity;
				break;
            case SDLK_LEFT:
				vx -= velocity;
				break;
            case SDLK_RIGHT:
				vx += velocity;
				break;
			case SDLK_LSHIFT:
				if (e.type == SDL_KEYDOWN) {
					focused = true;
					vx /= FVELOCITY;
					vy /= FVELOCITY;
				} else {
					focused = false;
					vx *= FVELOCITY;
					vy *= FVELOCITY;
				}
			default:
				break;
        }
    }

	int s;
	if (vx < 0) {
		s = Player::Sprite::LEFT;
	} else if (vx > 0) {
		s = Player::Sprite::RIGHT;
	} else {
		s = Player::Sprite::CENTER;
	}
	
	if (focused) {
		s += Player::Sprite::FOCUS;
	}

	sprite.setSID(s);
}

void Player::move(void)
{
	x += vx;
	if (0 > x || x + sprite.getSWidth() > SCREEN_WIDTH) {
		x -= vx;
	}

	y += vy;
	if (0 > y || y + sprite.getSHeight() > SCREEN_HEIGHT) {
		y -= vy;
	}
}

void Player::render(void) const
{
	sprite.render(x, y);
}

