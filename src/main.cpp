/**
 * Perfect Ostrove Blossom Main.
 * Alex Striff.
 */

#include "pob.h"
#include "ptexture.h"
#include "ptimer.h"
#include "stage.h"

size_t SCREEN_WIDTH  = 720;
size_t SCREEN_HEIGHT = 720;
size_t SCREEN_FPS    = 60;
size_t GFX_FPS       = SCREEN_FPS;
double SCREEN_TICKS  = 1e3 / SCREEN_FPS;
double gFPS          = (double) SCREEN_FPS;

SDL_Window   *gWindow   = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Surface  *gImage    = NULL;
TTF_Font     *gFont     = NULL;

PTexture   gBgTexture;
// PTexture   gTextTexture;
// PTexture   gFPSTexture;
FPSmanager gFPSManager;

std::vector<Stage> gStages;

bool init(void)
{
	fprintf(stderr,
			"\n"
			"\tPerfect Ostrove Blossom %10s\n"
			"\t==================================\n",
			VERSION);

	// Initialize SDL.
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "SDL could not initialize! SDL Error: %s\n",
				SDL_GetError());
		return false;
	}

	// Setup the GFX FPS manager.
	SDL_initFramerate(&gFPSManager);
	SDL_setFramerate(&gFPSManager, GFX_FPS);

	// Create the window.
	auto window_flags
		= SDL_WINDOW_SHOWN
		| SDL_WINDOW_BORDERLESS;

	gWindow = SDL_CreateWindow("SDL Test",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);

	if (!gWindow) {
		fprintf(stderr, "Window could not be created! SDL Error: %s\n",
				SDL_GetError());
		return false;
	}

	// Create the renderer for the window.
	auto renderer_flags
		= SDL_RENDERER_PRESENTVSYNC;
		// = 0;

	gRenderer = SDL_CreateRenderer(
			gWindow, -1, renderer_flags | SDL_RENDERER_ACCELERATED);
	if (!gRenderer) {
		gRenderer = SDL_CreateRenderer(
				gWindow, -1, renderer_flags | SDL_RENDERER_SOFTWARE);
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

	// Initialize SDL_image.
	auto img_flags
		= IMG_INIT_JPG
		| IMG_INIT_PNG
		| IMG_INIT_TIF;

	if (!(IMG_Init(img_flags) & img_flags)) {
		fprintf(stderr, "SDL_image could not be initialized! IMG Error: %s\n",
				IMG_GetError());
		return false;
	}

	// Initialize SDL_ttf.
	if (TTF_Init() == -1) {
		fprintf(stderr, "SDL_ttf could not be initialized! TTF Error: %s\n",
				TTF_GetError());
		return false;
	}

	return true;
}

void quit(int status)
{
	// Free stages.
	for (auto&& s: gStages) {
		s.free();
	}

	// Free surfaces.
	SDL_FreeSurface(gImage);
	gImage = NULL;

	// Destroy textures.
	gBgTexture.free();
	// gTextTexture.free();
	// gFPSTexture.free();
	for (auto&& b: BULLETS) {
		b.texture->free();
		b.texture.reset();
	}

	// Destroy renderer.
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	// Destroy window.
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	// Shut down SDL and its extensions.
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	fprintf(stderr,
			"\n" "\tGoodbye!\n"
			"\n");
	exit(status);
}

bool load_media(void)
{
	fprintf(stderr, "\tMEDIA_PATH\t: '%s'\n", MEDIA_PATH);

	// Load the background texture.
	if (!gBgTexture.load("background.png")) {
		fputs("PTexture '%s' could not be loaded!\n", stderr);
		return false;
	}

	// Get the default font.
	gFont = TTF_OpenFont(MEDIA_PATH DEFAULT_FONT, 72);
	if (!gFont) {
		fprintf(stderr, "Could not load default font! TTF Error: %s\n",
				TTF_GetError());
		return false;
	}

	// Render title text.
	// SDL_Color textColor = { 255, 0, 255 };
	// if (!gTextTexture.load_text("Perfect Ostrove Blossom", textColor)) {
	// 	fputs("Failed to render title text!\n", stderr);
	// 	quit(EXIT_FAILURE);
	// }

	// Load the bullet textures.
	for (auto& b: BULLETS) {
		if (strlen(b.sprite_file) > 0) {
			b.texture->load(b.sprite_file, {255, 0, 0, 255});
		}
	}

	fputc('\n', stderr);
	return true;
}

int main(int argc, const char **argv)
{
	// Initialize.
	if (!init()) {
		fputs("Failed to initialize!\n", stderr);
		quit(EXIT_FAILURE);
	}

	// Load media.
	if (!load_media()) {
		fputs("Failed to load media!\n", stderr);
		quit(EXIT_FAILURE);
	}

	// Create game objects.
	SDL_Event e;
	PTimer    fpsTimer;
	// SDL_Color textColor     = { 255, 0, 255 };
	double    angle         = 0.0;
	bool      user_quit     = false;

	double xd = +64 + SCREEN_WIDTH  / 2;
	double yd = -64 + SCREEN_HEIGHT / 2;
	auto d = std::make_shared<Danmaku>(
			xd, yd,
			M_PI / 4,
			830, 10,
			0,  0,
			true);

	for (double t = 2 * M_PI / 6; t < 2 * M_PI; t += 2 * M_PI / 6) {
		double xp = 128 * cos(t);
		double yp = 128 * sin(t);
		auto b    = std::make_shared<Danmaku>(xp, yp, t, 15*t, 1*t, 0, 0);
		d->addPObject(b);
	}

	// Add the danmaku to a stage.
	Stage s1;
	s1.addPObject(d);
	gStages.push_back(s1);

	// Create the player.
	Player player("player_sprites.png");
	player.sprite.setSprite(Player::Sprite::CENTER);
	player.sprite.setColor(48, 176, 255);
	player.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	std::stringstream logText;

	// Main game loop.
	fpsTimer.start();
	int countedFrames = 0;
	bool hit = false;
	while (!user_quit) {
		// Calclulate FPS.
		double meanFPS = countedFrames / (fpsTimer.ticks() / 1e3);
		if (meanFPS > 1e6) { // Extremely high FPS are erroneous.
			meanFPS = 0.0;
		}
		gFPS = meanFPS;
		if (std::isnan(gFPS) || gFPS == 0.0) {
			gFPS = SCREEN_FPS;
		}

		// Handle events on queue.
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
				case SDL_QUIT:
					user_quit = true;
					break;
				case SDL_KEYDOWN:
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
				case SDL_KEYUP:
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

		// Add more bullets!
		if (countedFrames % 2 == 0) {
			auto n = std::make_shared<Bullet>(
					0, 0,
					player.angleFrom(d->x, d->y),
					0.1, 0,
					-0.01, 0);
			n->setType(BulletType::RECT);
			d->addPObject(n);
		}

		if (countedFrames % 5 == 0) {
			d->map([d](std::shared_ptr<PObject> obj, std::shared_ptr<Danmaku> dobj, size_t di)
					{
					if (dobj) {
					for (double a = 2 * M_PI / 6; a < 2 * M_PI; a += 2 * M_PI / 6) {
					auto q = std::make_shared<Bullet>(
							d->x, d->y,
							(dobj->t)*a,
							15, 0,
							-1, 0);
					q->setType(BulletType::CIRCLE);
					dobj->addPObject(q);
					}
					}
					});
		}

		// Update the stage.
		std::for_each(gStages.begin(), gStages.end(),
				[](Stage& s){ s.update(); });

		// Move the player.
		// player.move(timeStep);
		player.move(1.0 / gFPS);

		// Check player collision with scene objects.
		Hitbox dh = d->getHitbox();
		Hitbox ph = player.hitbox();
		if (player.hitbox().intersects(dh)) {
			hit = true;
			player.sprite.setColor(255, 128, 192);
		} else {
			hit = false;
			player.sprite.setColor(48, 176, 255);
		}

		// Clear the screen.
		SDL_SetRenderDrawColor(gRenderer, 0x88, 0x88, 0x88, 0xff);
		SDL_RenderClear(gRenderer);

		// Copy the background image.
		Uint8 red   = 128 + ((1 * countedFrames / 3) % 63);
		Uint8 green = 128 + ((4 * countedFrames / 3) % 127);
		Uint8 blue  = 128 + ((3 * countedFrames / 3) % 159);
		gBgTexture.setColor(red, green, blue);
		gBgTexture.render(SCREEN_WIDTH  / 2, SCREEN_HEIGHT / 2, 1024, 1024,
				NULL, angle, NULL, SDL_FLIP_NONE);

		// angle += 2*M_PI / 64;
		angle += (SCREEN_FPS / gFPS) * 2*M_PI / 64;

		// Draw the player.
		player.render();

		// Draw the stage.
		std::for_each(gStages.begin(), gStages.end(),
				[](Stage& s){ s.render(); });

		// Draw text.
		// gTextTexture.render(SCREEN_WIDTH / 2, 36);
		// gFPSTexture.render((SCREEN_WIDTH + gFPSTexture.width()) / 2,
		// 		SCREEN_HEIGHT - gFPSTexture.height() / 2);

		// Draw a crosshair line of dots.
		for (size_t i = 0; i < SCREEN_HEIGHT; i += 3)
		{
			pixelRGBA(gRenderer, SCREEN_WIDTH / 2, i, 0, 255, 255, 127);
		}
		for (size_t i = 0; i < SCREEN_WIDTH; i += 3)
		{
			pixelRGBA(gRenderer, i, SCREEN_HEIGHT / 2, 0, 255, 255, 127);
		}

		// Log and developer information text.
		stringRGBA(gRenderer, 8, 8,  "Perfect Ostrove Blossom", 255, 255, 255, 255);

		logText.str("");
		logText
			<< "       FPS: "
			<< (round(meanFPS * 100.0)) / 100.0;
		stringRGBA(gRenderer, 8, 24, logText.str().c_str(), 255, 255, 255, 255);

		logText.str("");
		logText
			<< "    Player: "
			<< (hit ? "Hit" : "OK");
		stringRGBA(gRenderer, 8, 32, logText.str().c_str(), 255, 255, 255, 255);

		int rects = (int) (ph.getRects().size() + dh.getRects().size());
		logText.str("");
		logText
			<< "Rectangles: "
			<< rects;
		stringRGBA(gRenderer, 8, 40, logText.str().c_str(), 255, 255, 255, 255);

		int circles = (int) (ph.getCircles().size() + dh.getCircles().size());
		logText.str("");
		logText
			<< "   Circles: "
			<< circles;
		stringRGBA(gRenderer, 8, 48, logText.str().c_str(), 255, 255, 255, 255);

		logText.str("");
		logText
			<< "     Total: "
			<< circles + rects;
		stringRGBA(gRenderer, 8, 56, logText.str().c_str(), 255, 255, 255, 255);

		// Update the screen.
		SDL_RenderPresent(gRenderer);
		countedFrames++;
	}

	quit(EXIT_SUCCESS);
}

