/**
 * SDL_Texture Wrapper Class.
 * Alex Striff.
 */

#ifndef PTEXTURE_H
#define PTEXTURE_H

#include "common.h"

class PTexture
{
	protected:
		int w, h, sw, sh, sid;
		SDL_Rect    *sprite_box, sbox;
		SDL_Texture *texture;

	public:
		explicit PTexture():
			w(0),
			h(0),
			sw(0),
			sh(0),
			sid(0),
			sprite_box(NULL),
			sbox({0, 0, 0, 0}),
			texture(NULL) {
				setBlendMode(SDL_BLENDMODE_BLEND);
			}

		// A texture is non-copyable. What can be done with a hypothetical copy
		// can and should be done with the original. Use move semantics instead.
		explicit PTexture(PTexture& t)    = delete;
		PTexture& operator=(PTexture& t)  = delete;
		explicit PTexture(PTexture&& t)   = default;
		PTexture& operator=(PTexture&& t) = default;

		~PTexture();
		void free(void);

		bool load(const std::string& filename, SDL_Color color = {0, 0, 0, 0});
		bool load_text(const std::string& text, SDL_Color color);
		bool load_text(const std::string& text, SDL_Color color, TTF_Font *font);

		bool createBlank(
				int width, int height,
				SDL_TextureAccess access = SDL_TEXTUREACCESS_STREAMING);

		void setColor(Uint8 red, Uint8 green, Uint8 blue);
		void setBlendMode(SDL_BlendMode blending);
		void setAlpha(Uint8 alpha);
		void setGrid(int w, int h);
		void setSprite(int id);

		void render(int x, int y) const;
		void render(int x, int y, int w, int h) const;
		void render(int x, int y, int w, int h,
				const SDL_Rect *const clip) const;
		void render(int x, int y,
				const SDL_Rect  *const clip, double angle,
				const SDL_Point *const center, SDL_RendererFlip flip) const;
		void render(int x, int y, int w, int h,
				const SDL_Rect  *const clip, double angle,
				const SDL_Point *const center, SDL_RendererFlip flip) const;

		SDL_Texture *setRenderTarget(void);

		int width(void)   const;
		int height(void)  const;
		int swidth(void)  const;
		int sheight(void) const;
		int sprite(void)  const;
		SDL_Rect rect(void) const;
		SDL_Rect *sbox_ptr(void) const;
		SDL_Texture *texture_ptr(void) const;
};
COMMON_VERIFY_MOVE(PTexture);

using PTexturePointer = std::shared_ptr<PTexture>;

#endif /* PTEXTURE_H */

