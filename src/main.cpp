/**
 * Perfect Ostrove Blossom Main.
 * Alex Striff.
 */

#include "pob.h"
#include "ptexture.h"
#include "ptimer.h"
#include "player.h"
#include "danmaku.h"
#include "bullet.h"

/**
 * Screen dimensions.
 */
int SCREEN_WIDTH  = 720;
int SCREEN_HEIGHT = 720;

/**
 * Timing variables.
 */
int    SCREEN_FPS   = 120;
double SCREEN_TICKS = 1e3 / SCREEN_FPS;

/**
 * Global SDL variables.
 */
SDL_Window   *gWindow   = NULL; /**< The window to render to.            */
SDL_Renderer *gRenderer = NULL; /**< The renderer for the window.        */
SDL_Surface  *gImage    = NULL; /**< A image to be loaded and displayed. */

/**
 * Local SDL variables.
 */
TTF_Font     *gFont;        /**< The default font.                   */
PTexture      gBgTexture;   /**< The background texture.             */
PTexture      gTextTexture; /**< A texture used for displaying text. */
PTexture      gFPSTexture;  /**< A texture used for displaying text. */

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
#ifdef VSYNC
	int renderer_flags = SDL_RENDERER_PRESENTVSYNC;
#else
	int renderer_flags = 0;
#endif /* VSYNC */
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

	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xff);

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
	for (size_t i = 0; i < BULLETS_LENGTH; i++) {
		BULLETS[i].texture.free();
	}

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
#ifdef VSYNC
	bool vsync = true;
#else
	bool vsync = false;
#endif /* VSYNC */
	fprintf(stderr, "\tVSYNC STATUS\t: %s\n", vsync ? "On" : "Off; FPS cap");

	fprintf(stderr, "\tMEDIA_PATH\t: '%s'\n", MEDIA_PATH);

	/* Load the background texture. */
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

	/* Load the bullet textures. */
	for (size_t i = 0; i < BULLETS_LENGTH; i++) {
		if (strlen(BULLETS[i].sprite_file) > 0) {
			BULLETS[i].texture.load(BULLETS[i].sprite_file, {255, 0, 0, 255});
		}
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
	PTimer    stepTimer;
	SDL_Color textColor     = { 255, 0, 255 };
	int       countedFrames = 0;
	double    angle         = 0.0;
	bool      user_quit     = false;

	double xd = +64 + SCREEN_WIDTH  / 2;
	double yd = -64 + SCREEN_HEIGHT / 2;
	auto d = std::make_shared<Danmaku>(
			xd, yd,
			M_PI / 4,
			83, 1,
			0,  0,
			true);

	for (double t = 2 * M_PI / 6; t < 2 * M_PI; t += 2 * M_PI / 6) {
		double xp = 128 * cos(t);
		double yp = 128 * sin(t);
		auto b    = std::make_shared<Danmaku>(xp, yp, t, 15*t, 1*t, 0, 0);

		/* Hitbox    h; */
		/* SDL_Rect  r = {-8, -8, 16, 16}; */
		/* h.add(r); */
		/* b->setHitbox(h); */
		d->addPObject(b);
	}

	/* Hitbox    h; */
	/* Circle    c; */
	/* c = {0, 0, 16}; */
	/* h.add(c); */
	/* d->setHitbox(h); */

	Player player("player_sprites.png");
	player.sprite.setSID(Player::Sprite::CENTER);
	player.sprite.setColor(255, 0, 255);
	player.setPosition(SCREEN_WIDTH / 2, 4 * SCREEN_HEIGHT / 5);
	fprintf(stderr, "\tPlayer hitbox count: (%d, %d)\n",
			(int) player.getHitbox().getRects().size(),
			(int) player.getHitbox().getCircles().size());
	std::stringstream timeText;

	fpsTimer.start();
	while (!user_quit) {
		/* Calculate real time step. */
		double timeStep = stepTimer.getTicks() / 1e3;
		stepTimer.start();
		d->start();

		/* Calclulate FPS. */
		double meanFPS = countedFrames / (fpsTimer.getTicks() / 1e3);
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

		/* Add more! */
		if (countedFrames % 2 == 0) {
			auto n = std::make_shared<Bullet>(
					0, 0,
					player.angleFrom(d->x, d->y),
					50, 0,
					0, 0);
			n->setType(BulletType::RECT);
			d->addPObject(n);
		}

		if (countedFrames % SCREEN_FPS == 0) {
			d->map([d](std::shared_ptr<PObject> obj, std::shared_ptr<Danmaku> dobj, size_t di)
					{
					if (dobj) {
					for (double a = 2 * M_PI / 6; a < 2 * M_PI; a += 2 * M_PI / 6) {
					auto q = std::make_shared<Bullet>(
							d->x, d->y,
							(dobj->t)*a,
							15, 0,
							5, 0);
					q->setType(BulletType::CIRCLE);
					dobj->addPObject(q);
					}
					}
					});
		}

		/* Update the danmaku. */
		d->update();

		/* Move the player. */
		player.move(timeStep);

		/* Check player collision with danmaku. */
		Hitbox dh = d->getHitbox();
		Hitbox ph = player.getHitbox();
		fprintf(stderr, "\tTotal hitboxes: (%d, %d)\r",
				(int) (ph.getRects().size()   + dh.getRects().size()),
				(int) (ph.getCircles().size() + dh.getCircles().size()));

		if (player.getHitbox().intersects(dh)) {
			fputs("Intersection! ", stderr);
		}

		/* Clear the screen. */
		SDL_SetRenderDrawColor(gRenderer, 0x88, 0x88, 0x88, 0xff);
		SDL_RenderClear(gRenderer);

		/* Copy the background image. */
		/* Uint8 red   = rand() * (int)(255); */
		/* Uint8 green = rand() * (int)(255); */
		/* Uint8 blue  = rand() * (int)(255); */
		Uint8 red   = 128 + ((1 * countedFrames / 3) % 63);
		Uint8 green = 128 + ((4 * countedFrames / 3) % 127);
		Uint8 blue  = 128 + ((3 * countedFrames / 3) % 159);
		gBgTexture.setColor(red, green, blue);
		gBgTexture.render(SCREEN_WIDTH  / 2, SCREEN_HEIGHT / 2, 1024, 1024,
				NULL, angle, NULL, SDL_FLIP_NONE);

		angle += 2*M_PI / 64;

		/* Draw the player. */
		player.render();

		/* Draw the danmaku. */
		d->render();

		/* Draw text. */
		gTextTexture.render(SCREEN_WIDTH / 2, 36);
		gFPSTexture.render((SCREEN_WIDTH + gFPSTexture.getWidth()) / 2,
				SCREEN_HEIGHT - gFPSTexture.getHeight() / 2);

		/* Draw a crosshair line of black dots. */
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xff);
		for (int i = 0; i < SCREEN_HEIGHT; i += 3)
		{
			SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, i);
		}
		for (int i = 0; i < SCREEN_WIDTH; i += 3)
		{
			SDL_RenderDrawPoint(gRenderer, i, SCREEN_HEIGHT / 2);
		}


		/* Update the screen. */
		SDL_RenderPresent(gRenderer);
		countedFrames++;

#ifndef VSYNC
		/* Wait if the frame finished early. */
		double frameTicks = stepTimer.getTicks();
		if (frameTicks < 1e3 / SCREEN_TICKS) {
			SDL_Delay(SCREEN_TICKS - frameTicks);
		}
#endif /* VSYNC */
	}

	quit(EXIT_SUCCESS);
}

