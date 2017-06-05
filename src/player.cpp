#include "player.h"

Player::~Player()
{
	sprite.free();
}

void Player::handleEvent(SDL_Event &e)
{
	/* Update key states. */
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
				up_last = true;
				up      = true;
				ymotion++;
				break;
            case SDLK_DOWN:
				up_last = false;
				down    = true;
				ymotion++;
				break;
            case SDLK_LEFT:
				left_last = true;
				left      = true;
				xmotion++;
				break;
            case SDLK_RIGHT:
				left_last = false;
				right     = true;
				xmotion++;
				break;
			case SDLK_LSHIFT:
				focused = true;
			default:
				break;
        }
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
				up = false;
				ymotion--;
				break;
            case SDLK_DOWN:
				down = false;
				ymotion--;
				break;
            case SDLK_LEFT:
				left = false;
				xmotion--;
				break;
            case SDLK_RIGHT:
				right = false;
				xmotion--;
				break;
			case SDLK_LSHIFT:
				focused = false;
			default:
				break;
        }
    }

	int velocity = focused ? VELOCITY / FVELOCITY : VELOCITY;

	/* Set the x velocity. */
	if (xmotion == 0) {
		vx = 0;
	} else {
		if ((left_last && left) || !right) {
			vx = -velocity;
		} else {
			vx = +velocity;
		}
	}

	/* Set the y velocity. */
	if (ymotion == 0) {
		vy = 0;
	} else {
		if ((up_last && up) || !down) {
			vy = -velocity;
		} else {
			vy = +velocity;
		}
	}

	/* Set player sprite based on direction of motion. */
	int s;
	if (vx < 0) {
		s = Player::Sprite::LEFT;
	} else if (vx > 0) {
		s = Player::Sprite::RIGHT;
	} else {
		s = Player::Sprite::CENTER;
	}

	sprite.setSID(focused ? s + Player::Sprite::FOCUS : s);
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

Hitbox Player::getHitbox(void) const
{
	Hitbox h;
	Circle hit_circle;

	hit_circle.x = x + (sprite.getSWidth()  / 2);
	hit_circle.y = y + (sprite.getSHeight() / 2);
	hit_circle.r = 8;
	h.addCircle(hit_circle);

	return h;
}

