#include "ptexture.h"

PTexture::~PTexture()
{
	free();
}

void PTexture::free(void)
{
	/* Free the texture if it exists. */
	if (texture) {
		SDL_DestroyTexture(texture);
		texture = NULL;
		width   = 0;
		height  = 0;
	}
}

bool PTexture::load(std::string filename)
{
	/* Remove preexisting texture just in case. */
	free();

	std::string path        = std::string(MEDIA_PATH) + filename;
	SDL_Texture *tmptexture = NULL;
	SDL_Surface *loaded     = IMG_Load(path.c_str());
	if (!loaded) {
		fprintf(stderr, "Image surface '%s' could not be loaded! IMG Error: %s\n",
				path.c_str(), IMG_GetError());
	} else {
		tmptexture = SDL_CreateTextureFromSurface(gRenderer, loaded);
		if (!tmptexture) {
			fprintf(stderr, "Texture could not be created from '%s'! SDL Error: %s\n",
					path.c_str(), SDL_GetError());
		}

		width  = loaded->w;
		height = loaded->h;
		SDL_FreeSurface(loaded);
	}

	texture = tmptexture;
	return (texture != NULL);
}

bool PTexture::load_text(std::string text, SDL_Color color)
{
	return load_text(text, color, gFont);
}

bool PTexture::load_text(std::string text, SDL_Color color, TTF_Font *font)
{
	/* Remove preexisting texture just in case. */
	free();
	
	/* Render text surface. */
	SDL_Surface *text_surface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (!text_surface) {
		fprintf(stderr, "Could not render text surface! TTF Error: %s\n",
				TTF_GetError());
	}

	texture = SDL_CreateTextureFromSurface(gRenderer, text_surface);
	if (!texture) {
		fprintf(stderr, "Could not create texture from rendered text! SDL Error: %s\n",
				SDL_GetError());
	}

	width  = text_surface->w;
	height = text_surface->h;
	SDL_FreeSurface(text_surface);

	return (texture != NULL);
}

void PTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	/* Modulate the color of the texture. */
	SDL_SetTextureColorMod(texture, red, green, blue);
}

void PTexture::setBlendMode(SDL_BlendMode blending)
{
	/* Set blending function. */
	SDL_SetTextureBlendMode(texture, blending);
}

void PTexture::setAlpha(Uint8 alpha)
{
	/* Modulate the texture's alpha channel. */
	SDL_SetTextureAlphaMod(texture, alpha);
}

void PTexture::render(int x, int y) const
{
	render(x, y, width, height);
}

void PTexture::render(int x, int y, int w, int h) const
{
	render(x, y, w, h, NULL);
}

void PTexture::render(int x, int y, int w, int h, SDL_Rect *clip) const
{
	render(x, y, w, h, clip, 0.0, NULL, SDL_FLIP_NONE);
}

void PTexture::render(int x, int y, SDL_Rect *clip,
		double angle, SDL_Point *center, SDL_RendererFlip flip) const
{
	render(x, y, width, height, clip, angle, center, flip);
}

void PTexture::render(int x, int y, int w, int h, SDL_Rect *clip,
		double angle, SDL_Point *center, SDL_RendererFlip flip) const
{
	/* Create the rendering SDL_Rect. */
	SDL_Rect render_rect = {
		x, y,
		w, h,
	};

	/* Clip the rect if specified. */
	if (clip) {
		render_rect.w = clip->w;
		render_rect.h = clip->h;
	}

	/* Render the texture to the screen. */
	SDL_RenderCopyEx(gRenderer, texture, clip, &render_rect,
			angle, center, flip);
}

int PTexture::getWidth(void) const
{
	return width;
}

int PTexture::getHeight(void) const
{
	return height;
}

