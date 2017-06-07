#include "bulletdata.h"

static std::vector<SDL_Rect> NONE_RECTS   = std::vector<SDL_Rect>();
static std::vector<Circle>   NONE_CIRCLES = std::vector<Circle>();

static std::vector<SDL_Rect> CIRCLE_RECTS = NONE_RECTS;
static std::vector<Circle> CIRCLE_CIRCLES = {
	{0, 0, 5},
};

static std::vector<SDL_Rect> RECT_RECTS = {
	{-5, -5, 10, 10},
};
static std::vector<Circle> RECT_CIRCLES = NONE_CIRCLES;

size_t     BULLETS_LENGTH = 3;
BulletData BULLETS[] = {
	{
		BulletType::NONE,
		"",
		Hitbox(NONE_RECTS, NONE_CIRCLES),
	},
	{
		BulletType::CIRCLE,
		"circle.png",
		Hitbox(CIRCLE_RECTS, CIRCLE_CIRCLES),
	},
	{
		BulletType::RECT,
		"rect.png",
		Hitbox(RECT_RECTS, RECT_CIRCLES),
	},
};

