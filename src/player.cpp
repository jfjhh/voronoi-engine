#include "player.h"

Player::~Player()
{
	sprite.free();
}

void Player::handleEvent(const SDL_Event &e)
{
	// Update key states.
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

	// Set the x velocity.
	if (xmotion == 0) {
		vx = 0;
	} else {
		if ((left_last && left) || !right) {
			vx = -velocity;
		} else {
			vx = +velocity;
		}
	}

	// Set the y velocity.
	if (ymotion == 0) {
		vy = 0;
	} else {
		if ((up_last && up) || !down) {
			vy = -velocity;
		} else {
			vy = +velocity;
		}
	}

	// Set player sprite based on direction of motion.
	int s;
	if (vx < 0) {
		s = Player::Sprite::LEFT;
	} else if (vx > 0) {
		s = Player::Sprite::RIGHT;
	} else {
		s = Player::Sprite::CENTER;
	}

	sprite.setSprite(focused ? s + Player::Sprite::FOCUS : s);
}

void Player::move(double time)
{
	double hw = sprite.swidth()  / 2;
	double hh = sprite.sheight() / 2;

	x += vx * time;
	x = std::max(std::min(x, SCREEN_WIDTH - hw), hw);

	y += vy * time;
	y = std::max(std::min(y, SCREEN_HEIGHT - hh), hh);
}

void Player::render(void) const
{
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0xff, 0x00, 0xff);
	sprite.render(x, y);
	hbox.render();
}

double Player::angleFrom(double xf, double yf) const
{
	return atan2(y - yf, x - xf);
}

Hitbox Player::hitbox(void) const
{
	Hitbox h = hbox;
	h.translate(x, y);
	return h;
}

double Player::getX(void) const
{
	return x;
}

double Player::getY(void) const
{
	return y;
}

void Player::setPosition(double px, double py)
{
	double hw = sprite.swidth()  / 2;
	double hh = sprite.sheight() / 2;

	x = std::min(std::max(hw, px), SCREEN_WIDTH  - hw);
	y = std::min(std::max(hh, py), SCREEN_HEIGHT - hh);
}

