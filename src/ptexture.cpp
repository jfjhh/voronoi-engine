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
		pixels  = NULL;
		width   = 0;
		height  = 0;
		swidth  = 0;
		sheight = 0;
	}
}

bool PTexture::load(std::string filename, SDL_Color color)
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
		width   = loaded->w;
		height  = loaded->h;
		swidth  = width;
		sheight = height;

		if (color.a != 0) {
			const SDL_PixelFormat *format = loaded->format;
			void *pixels = loaded->pixels;

			for (Uint32 i = 0; i < (Uint32) (width * height); i++) {
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

/* bool PTexture::load(std::string filename) */
/* { */
/* 	/1* Remove preexisting texture just in case. *1/ */
/* 	free(); */

/* 	std::string path        = std::string(MEDIA_PATH) + filename; */
/* 	SDL_Texture *tmptexture = NULL; /1* The final loaded texture. *1/ */
/* 	SDL_Surface *loaded     = IMG_Load(path.c_str()); */
/* 	if (!loaded) { */
/* 		fprintf(stderr, "Image surface '%s' could not be loaded! IMG Error: %s\n", */
/* 				path.c_str(), IMG_GetError()); */
/* 	} else { */
/* 		fprintf(stderr, "\tDEBUG\t\t: ALIVE!\t%p\t%p\n", gWindow, loaded); */

/* 		/1* Try to get the window's surface. *1/ */
/* 		SDL_Surface *formatted; */
/* 		SDL_Surface *win_surface = SDL_GetWindowSurface(gWindow); */
/* 		if (!win_surface) { */
/* 			fprintf(stderr, "Could not get the window's surface! SDL Error: %s\n", */
/* 					SDL_GetError()); */

/* 			/1* Try anywway with an unconverted surface. *1/ */
/* 			/1* formatted = loaded; *1/ */
/* 			formatted = SDL_ConvertSurfaceFormat(loaded, SDL_PIXELFORMAT_RGBA8888, 0); */
/* 		} else { */
/* 			/1* Convert loaded surface to display format. *1/ */
/* 			formatted = SDL_ConvertSurface(loaded, */
/* 					SDL_GetWindowSurface(gWindow)->format, 0); */
/* 		} */

/* 		if (!formatted) { */
/* 			fprintf(stderr, "Could not convert loaded surface to display format! SDL Error: %s\n", */
/* 					SDL_GetError()); */
/* 		} else { */
/* 			/1* tmptexture = SDL_CreateTexture(gRenderer, *1/ */
/* 			/1* 		SDL_GetWindowPixelFormat(gWindow), *1/ */
/* 			/1* 		SDL_TEXTUREACCESS_STREAMING, formatted->w, formatted->h); *1/ */
/* 			tmptexture = SDL_CreateTexture(gRenderer, */
/* 					SDL_PIXELFORMAT_RGBA8888, */
/* 					SDL_TEXTUREACCESS_STREAMING, formatted->w, formatted->h); */

/* 			if (!tmptexture) { */
/* 				fprintf(stderr, "Unable to create blank streamable texture! SDL Error: %s\n", */
/* 						SDL_GetError()); */
/* 			} else { */
/* 				/1* Lock texture for manipulation. *1/ */
/* 				SDL_LockTexture(tmptexture, NULL, &pixels, &pitch); */

/* 				/1* Copy the formatted pixels that were loaded before. *1/ */
/* 				memcpy(pixels, formatted->pixels, formatted->pitch * formatted->h); */

/* 				/1* Unlock texture to update. *1/ */
/* 				SDL_UnlockTexture(tmptexture); */

/* 				pixels  = NULL; */
/* 				width   = formatted->w; */
/* 				height  = formatted->h; */
/* 				swidth  = width; */
/* 				sheight = height; */
/* 			} */

/* 			if (formatted != loaded) { */
/* 				SDL_FreeSurface(formatted); */
/* 			} */
/* 		} */
/* 		SDL_FreeSurface(loaded); */
/* 	} */

/* 	texture = tmptexture; */
/* 	return (texture != NULL); */
/* } */

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

	width   = text_surface->w;
	height  = text_surface->h;
	swidth  = width;
	sheight = height;
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

void PTexture::setSGrid(int w, int h)
{
	if (0 >= w || w > width || 0 >= h || h > height) {
		swidth  = width;
		sheight = height;
	} else {
		swidth  = w;
		sheight = h;
	}
}

void PTexture::setSID(int id)
{
	if (0 >= id || id > (width / swidth) * (height / sheight)) {
		sid        = 0;
		sbox       = {0, 0, getWidth(), getHeight()};
		sprite_box = NULL;
	} else {
		int cols   = width / swidth;
		sid        = id;
		sbox       = {
			swidth * ((sid - 1) % cols), sheight * ((sid - 1) / cols),
			swidth,                      sheight
		};
		sprite_box = &sbox;
	}
}

void PTexture::render(int x, int y) const
{
	render(x, y, swidth, sheight);
}

void PTexture::render(int x, int y, int w, int h) const
{
	render(x, y, w, h, sprite_box);
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
		x - (w / 2), y - (h / 2),
		w,           h,
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

SDL_Rect PTexture::getRect(void) const
{
	/**
	 * Use -hw and -hh for the rectangle x and y, so that adding the x and y of
	 * an object's center gives a box that has it's center at the object's
	 * center.
	 */
	int hw = swidth  / 2;
	int hh = sheight / 2;
	SDL_Rect r = {
		-hw,    -hh,
		swidth, sheight,
	};

	return r;
}

Circle PTexture::getCircle(void) const
{
	int hw = swidth  / 2;
	int hh = sheight / 2;
	Circle c = {
		0, 0,
		std::min(hw, hh),
	};

	return c;
}

int PTexture::getWidth(void) const
{
	return width;
}

int PTexture::getHeight(void) const
{
	return height;
}

int PTexture::getSWidth(void) const
{
	return swidth;
}

int PTexture::getSHeight(void) const
{
	return sheight;
}

bool PTexture::lockTexture()
{
	return false;
}

bool PTexture::unlockTexture()
{
	return false;
}

void *PTexture::getPixels() const
{
	return NULL;
}

int PTexture::getPitch() const
{
	return 0;
}

