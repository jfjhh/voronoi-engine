/**
 * Common Header Information.
 * Alex Striff.
 */

#ifndef POB_H
#define POB_H

#ifndef MEDIA_PATH
#define MEDIA_PATH	"./media/"
#endif /* MEDIA_PATH */

#ifndef DEFAULT_FONT
#define DEFAULT_FONT	"jfjhh.ttf"
#endif /* DEFAULT_FONT */

#ifndef VERSION
#define VERSION	"v0.0.0"
#endif /* VERSION */

#include <stdlib.h>
#include <stdio.h>
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_framerate.h>
#include <SDL2/SDL2_gfxPrimitives.h>

/**
 * Screen dimensions.
 */
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

/**
 * Timing variables.
 */
extern int    SCREEN_FPS;
extern double SCREEN_TICKS;

/**
 * Global SDL variables.
 */
extern SDL_Window   *gWindow;    /**< The window to render to.               */
extern SDL_Renderer *gRenderer;  /**< The renderer for the window.           */
extern SDL_Surface  *gImage;     /**< A image to be loaded and displayed.    */
extern TTF_Font     *gFont;      /**< The default font.                      */

#endif /* POB_H */

