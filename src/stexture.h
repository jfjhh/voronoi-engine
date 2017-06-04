/**
 * Sprite Sheet Texture Class.
 * Alex Striff.
 */

#ifndef STEXTURE_H
#define STEXTURE_H

#include "ptexture.h"

class STexture : public PTexture
{
	private:
		int sprite_width, sprite_height;

	public:
		/**
		 * Initializes the sprite sheet.
		 *
		 * By default, be a sprite sheet of one sprite, which is effectively an
		 * unmodified PTexture.
		 *
		 * Sprites are indexed from 0, left to right, top to bottom.
		 */
		STexture():
			PTexture(),
			sprite_width(width),
			sprite_height(height) {}

		/**
		 * Frees the texture.
		 */
		void free(void) override;

		/**
		 * Render the a sprite at the given coordinates.
		 */
		void render(int x, int y, int i) const;
		void render(int x, int y, int w, int h, int i) const;

		/**
		 * Set the dimensions of sprite cells in the sheet.
		 */
		void setSpriteWidth(int w);
		void setSpriteHeight(int h);

		/**
		 * Get the dimensions of sprite cells in the sheet.
		 */
		int getSpriteWidth(void) const;
		int getSpriteHeight(void) const;
};

#endif /* STEXTURE_H */

