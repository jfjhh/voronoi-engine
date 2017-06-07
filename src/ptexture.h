/**
 * SDL_Texture Wrapper Class.
 * Alex Striff.
 */

#ifndef PTEXTURE_H
#define PTEXTURE_H

#include "pob.h"
#include "circle.h"

class PTexture
{
	protected:
		int width, height, swidth, sheight, sid, pitch;
		SDL_Rect    *sprite_box, sbox;
		SDL_Texture *texture;
		void        *pixels;

	public:
		/**
		 * Initializes the texture.
		 */
		PTexture():
			width(0),
			height(0),
			swidth(0),
			sheight(0),
			sid(0),
			pitch(0),
			sprite_box(NULL),
			sbox({0, 0, 0, 0}),
			texture(NULL),
			pixels(NULL) {
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
		bool load(std::string filename, SDL_Color color = {0, 0, 0, 0});

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
		 * Set the sprite dimensions of a sprite sheet.
		 */
		void setSGrid(int w, int h);

		/**
		 * Set sprite id (sid), to change clipping box on texture.
		 */
		void setSID(int id);

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
		 * Gets the rectangle of the sprite's bounds.
		 */
		SDL_Rect getRect(void) const;

		/**
		 * Gets the inscribed circle of the sprite's bounds.
		 */
		Circle getCircle(void) const;

		/**
		 * Gets the texture's width.
		 */
		int getWidth(void) const;

		/**
		 * Gets the texture's height.
		 */
		int getHeight(void) const;

		/**
		 * Gets the texture's sprite width.
		 */
		int getSWidth(void) const;

		/**
		 * Gets the texture's sprite height.
		 */
		int getSHeight(void) const;

		/**
		 * Manipulate texture pixels.
		 */
		bool lockTexture();
		bool unlockTexture();
		void *getPixels() const;
		int getPitch() const;
};

#endif /* PTEXTURE_H */

