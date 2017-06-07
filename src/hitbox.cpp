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
	if (!SDL_HasIntersection(&u, &t)) {
		return false;
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
	SDL_Rect u = {0, 0, 0, 0};

	for (size_t i = 0; i < rects.size(); i++) {
		SDL_Rect cur = u;
		SDL_UnionRect(&cur, &rects[i], &u);
	}
	for (size_t i = 0; i < circles.size(); i++) {
		SDL_Rect cur = u;
		Circle c = circles[i];
		SDL_Rect circumrect = {
			c.x - c.r, c.y - c.r,
			2 * c.r,   2 * c.r,
		};
		SDL_UnionRect(&cur, &circumrect, &u);
	}

	return u;
}

void Hitbox::offset(int x, int y)
{
	for (size_t i = 0; i < rects.size(); i++) {
		rects[i].x += x;
		rects[i].y += y;
	}

	for (size_t i = 0; i < circles.size(); i++) {
		circles[i].x += x;
		circles[i].y += y;
	}
}

void Hitbox::render(void) const
{
	/* Draw rectangles. */
	for (size_t i = 0; i < rects.size(); i++) {
		SDL_RenderDrawRect(gRenderer, &rects[i]);
	}

	/* Draw circles, pixel by pixel. */
	for (size_t i = 0; i < circles.size(); i++) {
		for (float t = 0; t < 2 * M_PI; t += 1.0 / circles[i].r) {
			int cx = circles[i].x + (circles[i].r * cos(t));
			int cy = circles[i].y + (circles[i].r * sin(t));
			SDL_RenderDrawPoint(gRenderer, cx, cy);
		}
	}
}

std::vector<SDL_Rect> Hitbox::getRects(void) const
{
	return rects;
}

std::vector<Circle> Hitbox::getCircles(void) const
{
	return circles;
}

