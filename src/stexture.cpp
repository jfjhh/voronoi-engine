#include "stexture.h"

void STexture::free(void)
{
	PTexture::free();
	sprite_width  = 0;
	sprite_height = 0;
}

void STexture::render(int x, int y, int i) const
{
	render(x, y, sprite_width, sprite_height, i);
}

void STexture::render(int x, int y, int w, int h, int i) const
{
	/* Create the sprite's SDL_Rect. */
	int cols = width / sprite_width;
	SDL_Rect sprite_rect = {
		sprite_width * (i % cols), sprite_height * (i / cols),
		sprite_width,              sprite_height,
	};

	/* Create the rendering SDL_Rect. */
	SDL_Rect render_rect = {
		x, y,
		w, h,
	};

	/* Render the texture to the screen. */
	SDL_RenderCopy(gRenderer, texture, &sprite_rect, &render_rect);
}

void STexture::setSpriteWidth(int w)
{
	sprite_width = w;
}

void STexture::setSpriteHeight(int h)
{
	sprite_height = h;
}

int STexture::getSpriteWidth(void) const
{
	return sprite_width;
}

int STexture::getSpriteHeight(void) const
{
	return sprite_height;
}

