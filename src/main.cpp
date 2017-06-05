/**
 * Perfect Ostrove Blossom Main.
 * Alex Striff.
 */

#include "pob.h"
#include "ptexture.h"
#include "ptimer.h"
#include "player.h"

/**
 * Screen dimensions.
 */
int SCREEN_WIDTH  = 720;
int SCREEN_HEIGHT = 720;

/**
 * Global SDL variables.
 */
SDL_Window   *gWindow   = NULL; /**< The window to render to.               */
SDL_Renderer *gRenderer = NULL; /**< The renderer for the window.           */
SDL_Surface  *gImage    = NULL; /**< A image to be loaded and displayed.    */
TTF_Font     *gFont;            /**< The default font.                      */
PTexture      gBgTexture;       /**< The background texture.                */
PTexture      gTextTexture;     /**< A texture used for displaying text.    */
PTexture      gFPSTexture;      /**< A texture used for displaying text.    */

/**
 * Starts SDL and creates the window.
 */
bool init(void)
{
	fprintf(stderr,
			"\n"
			"\tPerfect Ostrove Blossom %10s\n"
			"\t==================================\n",
			VERSION);

	/* Initialize SDL. */
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "SDL could not initialize! SDL Error: %s\n",
				SDL_GetError());
		return false;
	}

	/* Create the window. */
	uint32_t window_flags =
		SDL_WINDOW_SHOWN |
		SDL_WINDOW_BORDERLESS;

	gWindow = SDL_CreateWindow("SDL Test",
			SDL_WINDOWPOS_UNDEFINED,  SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,             SCREEN_HEIGHT,
			window_flags);

	if (!gWindow) {
		fprintf(stderr, "Window could not be created! SDL Error: %s\n",
				SDL_GetError());
		return false;
	}

	/* Create the renderer for the window. */
	int renderer_flags = SDL_RENDERER_PRESENTVSYNC;
	gRenderer = SDL_CreateRenderer(gWindow, -1, renderer_flags | SDL_RENDERER_ACCELERATED);
	if (!gRenderer) {
		gRenderer = SDL_CreateRenderer(gWindow, -1, renderer_flags | SDL_RENDERER_SOFTWARE);
		if (!gRenderer) {
			fprintf(stderr, "Renderer could not be created! SDL Error: %s\n",
					SDL_GetError());
			return false;
		} else {
			fprintf(stderr, "Using fallback software renderer. SDL Error: %s\n",
					SDL_GetError());
		}
	}

	SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);

	/* Initialize SDL_image. */
	int img_flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
	if (!(IMG_Init(img_flags) & img_flags)) {
		fprintf(stderr, "SDL_image could not be initialized! IMG Error: %s\n",
				IMG_GetError());
		return false;
	}

	/* Initialize SDL_ttf. */
	if (TTF_Init() == -1) {
		fprintf(stderr, "SDL_ttf could not be initialized! TTF Error: %s\n",
				TTF_GetError());
		return false;
	}

	return true;
}

/**
 * Frees media and shuts down SDL.
 */
void quit(int status)
{
	/* Free surfaces. */
	SDL_FreeSurface(gImage);
	gImage = NULL;

	/* Destroy textures. */
	gBgTexture.free();
	gTextTexture.free();
	gFPSTexture.free();

	/* Destroy renderer. */
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	/* Destroy window. */
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	/* Shut down SDL and its extensions. */
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	fprintf(stderr,
			"\n" "\tGoodbye!\n"
			"\n");
	exit(status);
}

/**
 * Loads and optimizes the texture at MEDIA_PATH with the given filename.
 */
SDL_Texture *load_texture(std::string filename)
{
	std::string path       = std::string(MEDIA_PATH) + filename;
	SDL_Texture *texture   = NULL;
	SDL_Surface *loaded    = IMG_Load(path.c_str());
	if (!loaded) {
		fprintf(stderr, "Image surface '%s' could not be loaded! IMG Error: %s\n",
				path.c_str(), IMG_GetError());
	} else {
		texture = SDL_CreateTextureFromSurface(gRenderer, loaded);
		if (!texture) {
			fprintf(stderr, "Texture could not be created from '%s'! SDL Error: %s\n",
					path.c_str(), SDL_GetError());
		}
		SDL_FreeSurface(loaded);
	}

	return texture;
}

/**
 * Loads media.
 */
bool load_media(void)
{
	fprintf(stderr, "\tMEDIA_PATH\t: '%s'\n", MEDIA_PATH);

	if (!gBgTexture.load("circle_bullet.png")) {
		fputs("PTexture '%s' could not be loaded!\n", stderr);
		return false;
	}

	/* Get the default font. */
	gFont = TTF_OpenFont(MEDIA_PATH DEFAULT_FONT, 72);
	if (!gFont) {
		fprintf(stderr, "Could not load default font! TTF Error: %s\n",
				TTF_GetError());
		return false;
	}

	/* Render title text. */
	SDL_Color textColor = { 255, 0, 255 };
	if (!gTextTexture.load_text("Perfect Ostrove Blossom", textColor)) {
		fputs("Failed to render title text!\n", stderr);
		quit(EXIT_FAILURE);
	}

	fputc('\n', stderr);
	return true;
}

int main(int argc, const char **argv)
{
	/* Initialize. */
	if (!init()) {
		fputs("Failed to initialize!\n", stderr);
		quit(EXIT_FAILURE);
	}

	/* Load media. */
	if (!load_media()) {
		fputs("Failed to load media!\n", stderr);
		quit(EXIT_FAILURE);
	}

	/* Main loop. */
	SDL_Event e;
	PTimer    fpsTimer;
	SDL_Color textColor     = { 255, 0, 255 };
	int       countedFrames = 0;
	double    angle         = 0.0;
	bool      user_quit     = false;

	Player player("player_sprites.png");
	player.sprite.setSGrid(32, 32);
	player.sprite.setSID(Player::Sprite::CENTER);
	player.sprite.setColor(255, 0, 255);

	std::stringstream timeText;
	fpsTimer.start();

	while (!user_quit) {
		/* Calclulate FPS. */
		float meanFPS = countedFrames / (fpsTimer.getTicks() / 1e3);
		if (meanFPS > 1e6) { /* Extremely high FPS are erroneous. */
			meanFPS = 0;
		}

		/* Render FPS texture. */
		timeText.str("");
		timeText << "FPS: " << meanFPS;
		if (!gFPSTexture.load_text(timeText.str().c_str(), textColor)) {
			fputs("Could not render FPS texture!\n", stderr);
		}

		/* Handle events on queue. */
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
				case SDL_QUIT: /* User wants to close the window. */
					user_quit = true;
					break;
				case SDL_KEYDOWN: /* Key pressed. */
					switch (e.key.keysym.sym) {
						case SDLK_ESCAPE:
						case SDLK_q:
							user_quit = true;
							break;
						case SDLK_UP:
						case SDLK_DOWN:
						case SDLK_LEFT:
						case SDLK_RIGHT:
						case SDLK_LSHIFT:
							player.handleEvent(e);
							break;
						default:
							break;
					}
					break;
				case SDL_KEYUP: /* Key released. */
					switch (e.key.keysym.sym) {
						case SDLK_UP:
						case SDLK_DOWN:
						case SDLK_LEFT:
						case SDLK_RIGHT:
						case SDLK_LSHIFT:
							player.handleEvent(e);
							break;
						default:
							break;
					}
					break;
				default:
					break;
			}
		}

		player.move();

		/* Clear the screen. */
		SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderClear(gRenderer);

		/* Copy the background image. */
		Uint8 red   = rand() * (int)(255);
		Uint8 green = rand() * (int)(255);
		Uint8 blue  = rand() * (int)(255);
		gBgTexture.setColor(red, green, blue);
		gBgTexture.render((SCREEN_WIDTH - 512) / 2,
				(SCREEN_HEIGHT - 512) / 2,
				512, 512,
				NULL, angle, NULL, SDL_FLIP_NONE);

		angle += 2*M_PI / 16;

		/* Draw a crosshair line of pink dots. */
		SDL_SetRenderDrawColor(gRenderer, 0xff, 0x00, 0xff, 0xff);
		for (int i = 0; i < SCREEN_HEIGHT; i += 3)
		{
			SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, i);
		}
		for (int i = 0; i < SCREEN_WIDTH; i += 3)
		{
			SDL_RenderDrawPoint(gRenderer, i, SCREEN_HEIGHT / 2);
		}

		/* Draw the player. */
		player.render();

		/* Draw text. */
		gTextTexture.render((SCREEN_WIDTH - gTextTexture.getWidth()) / 2, 36);
		gFPSTexture.render(SCREEN_WIDTH / 2,
				SCREEN_HEIGHT - gFPSTexture.getHeight());

		/* Update the screen. */
		SDL_RenderPresent(gRenderer);
		countedFrames++;
	}

	quit(EXIT_SUCCESS);
}

