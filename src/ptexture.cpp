#include "ptexture.h"

PTexture::~PTexture()
{
	free();
}

void PTexture::free(void)
{
	// Free the texture if it exists.
	if (texture) {
		SDL_DestroyTexture(texture);
		texture = NULL;
		w  = 0;
		h  = 0;
		sw = 0;
		sh = 0;
	}
}

bool PTexture::load(const std::string& filename, SDL_Color color)
{
	// Remove preexisting texture just in case.
	free();

	std::string path        = std::string(MEDIA_PATH) + filename;
	SDL_Texture *tmptexture = NULL;
	SDL_Surface *loaded     = IMG_Load(path.c_str());
	if (!loaded) {
		fprintf(stderr, "Image surface '%s' could not be loaded! IMG Error: %s\n",
				path.c_str(), IMG_GetError());
	} else {
		w   = loaded->w;
		h  = loaded->h;
		sw  = w;
		sh = h;

		if (color.a != 0) {
			const SDL_PixelFormat *format = loaded->format;
			void *pixels = loaded->pixels;

			for (Uint32 i = 0; i < (Uint32) (w * h); i++) {
				Uint32 *pixel = (Uint32 *) pixels + i;
				Uint8 r = *pixel + color.r - (*pixel * color.r) / 255;
				Uint8 g = *pixel + color.g - (*pixel * color.g) / 255;
				Uint8 b = *pixel + color.b - (*pixel * color.b) / 255;
				*pixel = SDL_MapRGBA(format, r, g, b, *((Uint8 *) pixel + 3));
			}
		}

		tmptexture = SDL_CreateTextureFromSurface(gRenderer, loaded);
		if (!tmptexture) {
			fprintf(stderr, "Texture could not be created from '%s'! SDL Error: %s\n",
					path.c_str(), SDL_GetError());
		}

		SDL_FreeSurface(loaded);
	}

	texture = tmptexture;
	return (texture != NULL);
}

bool PTexture::load_text(const std::string& text, SDL_Color color)
{
	return load_text(text, color, gFont);
}

bool PTexture::load_text(
		const std::string& text, SDL_Color color, TTF_Font *font)
{
	// Remove preexisting texture just in case.
	free();
	
	// Render text surface.
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

	w   = text_surface->w;
	h  = text_surface->h;
	sw  = w;
	sh = h;
	SDL_FreeSurface(text_surface);

	return (texture != NULL);
}

bool PTexture::createBlank(
		int width, int height,
		SDL_TextureAccess access)
{
	if (!gRenderer || width <= 0 || height <= 0) {
		texture = NULL;
		return false;
	}
	texture = SDL_CreateTexture(
			gRenderer, SDL_PIXELFORMAT_RGBA8888, access, width, height);
	setBlendMode(SDL_BLENDMODE_BLEND);
	if (texture) {
		w = width;
		h = height;
	} else {
		fprintf(stderr, "Could not create blank texture! SDL Error: %s\n",
				SDL_GetError());
	}

	return (texture != NULL);
}

void PTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	// Modulate the color of the texture.
	SDL_SetTextureColorMod(texture, red, green, blue);
}

void PTexture::setBlendMode(SDL_BlendMode blending)
{
	// Set blending function.
	SDL_SetTextureBlendMode(texture, blending);
}

void PTexture::setAlpha(Uint8 alpha)
{
	// Modulate the texture's alpha channel.
	SDL_SetTextureAlphaMod(texture, alpha);
}

void PTexture::setGrid(int gw, int gh)
{
	if (0 >= gw || gw > w || 0 >= gh || gh > h) {
		sw = gw;
		sh = gh;
	} else {
		sw = gw;
		sh = gh;
	}
}

void PTexture::setSprite(int id)
{
	if (0 >= id || id > (w / sw) * (h / sh)) {
		sid        = 0;
		sbox       = {0, 0, w, h};
		sprite_box = NULL;
	} else {
		int cols   = w / sw;
		sid        = id;
		sbox       = {
			sw * ((sid - 1) % cols), sh * ((sid - 1) / cols),
			sw,                      sh
		};
		sprite_box = &sbox;
	}
}

void PTexture::render(int x, int y) const
{
	render(x, y, sw, sh);
}

void PTexture::render(int x, int y, double t) const
{
	render(x, y, sw, sh, sprite_box, t, NULL, SDL_FLIP_NONE);
}

void PTexture::render(int x, int y, int w, int h) const
{
	render(x, y, w, h, sprite_box);
}

void PTexture::render(
		int x, int y, int w, int h,
		const SDL_Rect *const clip) const
{
	render(x, y, w, h, clip, 0.0, NULL, SDL_FLIP_NONE);
}

void PTexture::render(
		int x, int y,
		const SDL_Rect  *const clip,   double angle,
		const SDL_Point *const center, SDL_RendererFlip flip = SDL_FLIP_NONE) const
{
	render(x, y, w, h, clip, angle, center, flip);
}

void PTexture::render(
		int x, int y, int w, int h,
		const SDL_Rect  *const clip,   double angle,
		const SDL_Point *const center, SDL_RendererFlip flip = SDL_FLIP_NONE) const
{
	// Create the rendering SDL_Rect.
	SDL_Rect render_rect = {
		x - (w / 2), y - (h / 2),
		w,           h,
	};

	// Clip the rect if specified.
	if (clip) {
		render_rect.w = clip->w;
		render_rect.h = clip->h;
	}

	// Render the texture to the screen.
	SDL_RenderCopyEx(gRenderer, texture, clip, &render_rect,
			angle * 180.0 / M_PI, center, flip);
}

SDL_Texture *PTexture::setRenderTarget(void)
{
	SDL_Texture *oldTarget = SDL_GetRenderTarget(gRenderer);
	SDL_SetRenderTarget(gRenderer, texture);
	return oldTarget;
}

int PTexture::width(void) const
{
	return w;
}

int PTexture::height(void) const
{
	return h;
}

int PTexture::swidth(void) const
{
	return sw;
}

int PTexture::sheight(void) const
{
	return sh;
}

int PTexture::sprite(void) const
{
	return sid;
}

SDL_Rect PTexture::rect(void) const
{
	return sbox;
}

SDL_Rect *PTexture::sbox_ptr(void) const
{
	return sprite_box;
}

SDL_Texture *PTexture::texture_ptr(void) const
{
	return texture;
}

