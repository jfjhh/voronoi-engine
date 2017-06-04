/**
 * SDL_Texture Wrapper Class.
 * Alex Striff.
 */

#ifndef PTEXTURE_H
#define PTEXTURE_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "pob.h"

class PTexture
{
	protected:
		int width, height;
		SDL_Texture *texture;

	public:
		/**
		 * Initializes the texture.
		 */
		PTexture():
			width(0),
			height(0),
			texture(NULL) {
				setBlendMode(SDL_BLENDMODE_BLEND);
			}

		/**
		 * Destroys the texture.
		 */
		~PTexture();

		/**
		 * Frees the texture.
		 */
		virtual void free(void);

		/**
		 * Loads a texture from a file.
		 */
		bool load(std::string filename);

		/**
		 * Create a text texture from a string.
		 */
		bool load_text(std::string text, SDL_Color color);
		bool load_text(std::string text, SDL_Color color, TTF_Font *font);

		/**
		 * Set color modulation.
		 */
		void setColor(Uint8 red, Uint8 green, Uint8 blue);

		/**
		 * Set alpha blend mode.
		 */
		void setBlendMode(SDL_BlendMode blending);

		/**
		 * Set alpha modulation.
		 */
		void setAlpha(Uint8 alpha);

		/**
		 * Renders the texture at the given coordinates.
		 */
		virtual void render(int x, int y) const;
		virtual void render(int x, int y, int w, int h) const;
		virtual void render(int x, int y, int w, int h, SDL_Rect *clip) const;
		virtual void render(int x, int y, SDL_Rect *clip,
				double angle, SDL_Point *center, SDL_RendererFlip flip) const;
		virtual void render(int x, int y, int w, int h, SDL_Rect *clip,
				double angle, SDL_Point *center, SDL_RendererFlip flip) const;

		/**
		 * Gets the texture's width.
		 */
		int getWidth(void) const;

		/**
		 * Gets the texture's height.
		 */
		int getHeight(void) const;
};

#endif /* PTEXTURE_H */

