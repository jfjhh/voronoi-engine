/**
 * Common Header Information.
 * Alex Striff.
 */

#ifndef COMMON_H
#define COMMON_H

#ifndef MEDIA_PATH
#define MEDIA_PATH "./media/"
#endif /* MEDIA_PATH */

#ifndef DEFAULT_FONT
#define DEFAULT_FONT "jfjhh.ttf"
#endif /* DEFAULT_FONT */

#ifndef VERSION
#define VERSION "v0.0.0"
#endif /* VERSION */

#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <memory>
#include <vector>
#include <string>
#include <sstream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_framerate.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "commont.h"

extern size_t SCREEN_WIDTH;
extern size_t SCREEN_HEIGHT;
extern size_t SCREEN_FPS;
extern size_t GFX_FPS;
extern double SCREEN_TICKS;
extern double gFPS, gTimeStep;

extern SDL_Window   *gWindow;
extern SDL_Renderer *gRenderer;
extern SDL_Surface  *gImage;
extern TTF_Font     *gFont;

#endif /* COMMON_H */

