#include "hitbox.h"

void Hitbox::add(SDL_Rect rect)
{
	rects.push_back(rect);
}

void Hitbox::add(Circle circle)
{
	circles.push_back(circle);
}

void Hitbox::add(const Hitbox h)
{
	std::vector<SDL_Rect> r = h.getRects();
	std::vector<Circle>   c = h.getCircles();
	rects.insert(rects.end(),      r.begin(),  r.end());
	circles.insert(circles.end(),  c.begin(),  c.end());
}

bool Hitbox::intersects(Hitbox h) const
{
	/* Try the union rects first. */
	SDL_Rect u = unionRect();
	SDL_Rect t = h.unionRect();
	if (SDL_HasIntersection(&u, &t)) {
		return true;
	}

	/* Compare all rects. */
	for (size_t i = 0; i < rects.size(); i++) {
		if (h.intersects(rects[i])) {
			return true;
		}
	}

	/* Compare all circles. */
	for (size_t i = 0; i < circles.size(); i++) {
		if (h.intersects(circles[i])) {
			return true;
		}
	}

	return false;
}

bool Hitbox::intersects(const SDL_Rect &r) const
{
	for (size_t i = 0; i < rects.size(); i++) {
		if (SDL_HasIntersection(&rects[i], &r)) {
			return true;
		}
	}
	for (size_t i = 0; i < circles.size(); i++) {
		if (Circle_HasIntersection(&circles[i], &r)) {
			return true;
		}
	}

	return false;
}

bool Hitbox::intersects(const Circle &c) const
{
	for (size_t i = 0; i < rects.size(); i++) {
		if (Circle_HasIntersection(&c, &rects[i])) {
			return true;
		}
	}
	for (size_t i = 0; i < circles.size(); i++) {
		if (Circle_HasIntersection(&c, &circles[i])) {
			return true;
		}
	}

	return false;
}

SDL_Rect Hitbox::unionRect(void) const
{
	SDL_Rect u = rects[0];

	for (size_t i = 1; i < rects.size(); i++) {
		SDL_Rect cur = u;
		SDL_UnionRect(&cur, &rects[i], &u);
	}

	return u;
}

std::vector<SDL_Rect> Hitbox::getRects(void) const
{
	return rects;
}

std::vector<Circle> Hitbox::getCircles(void) const
{
	return circles;
}

