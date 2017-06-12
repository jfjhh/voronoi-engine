#include "shape.h"

Shape::Shape(coord tw)
{
	t = 0.0;
	center = {0.0, 0.0, tw / 2.0};
	shapeTexture = std::make_shared<PTexture>();
	setTextureWidth(tw + 1.0);
}

Shape::Shape(coord tw, coord th): Shape(std::max(tw, th)) {}

void Shape::translate(coord x, coord y)
{
	for (auto&& v: chull) {
		v.translate(Vertex{x, y});
	}
	for (auto&& v: vhull) {
		v.translate(VoronoiVertex{x, y});
	}
	center.translate(VoronoiVertex{x, y});
}

void Shape::render(void) const
{
	for (const auto& v: chull) {
		pixelRGBA(gRenderer, v.x, v.y, 255, 255, 255, 255);
	}
	for (const auto& v: vhull) {
		circleRGBA(gRenderer, v.x, v.y, v.r, 255, 255, 255, 255);
	}
}

void Shape::renderTexture(coord add_rot) const
{
	if (!textureOK) return;
	SDL_Texture *old = shapeTexture->setRenderTarget();
	SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0x00);
	SDL_RenderClear(gRenderer);

	render();

	SDL_SetRenderTarget(gRenderer, old);
	shapeTexture->render(center.x, center.y, NULL, t + add_rot, NULL, SDL_FLIP_NONE);
}

bool Shape::setTextureWidth(int tw)
{
	textureSide = tw;
	return renewTexture();
}

bool Shape::renewTexture(void)
{
	return textureOK = shapeTexture->createBlank(
			(int) textureSide, (int) textureSide, SDL_TEXTUREACCESS_TARGET);
}

bool Shape::textureStatus(void)
{
	return textureOK;
}

void Shape::setAngle(coord to)
{
	t = to;
}

void Shape::rotate(coord by)
{
	setAngle(t + by);
}

coord Shape::angle(void) const
{
	return t;
}

Range Shape::projectOn(coord axis) const
{
	return project(t - axis);
}

Range Shape::project(coord on) const
{
	auto r = inverse_range;

	for (const auto& v: chull) {
		r.update(v.distanceTo() * cos(on));
	}

	return r;
}

VoronoiVertex Shape::vcenter(void) const
{
	return center;
}

ConvexHull Shape::vertices(void) const
{
	auto h = ConvexHull{};
	for (const auto& v: chull) {
		h.push_back(v.rotate(t, center));
	}
	return h;
}

VoronoiHull Shape::voronoiVertices(void) const
{
	// TODO: Add in voronoi approximation levels.
	// I.e. the default is the circumcircle (or should it be incircle?)
	// voronoi vertex (vcenter), then the next is the inscribed circle and N
	// tangent circles, for a polygon with N convex hull vertices, or N=2 for a
	// 3-circle ellipse, N=3 gives a 6-circle ellipse, etc. as a pseudo-fractal.
	auto h = VoronoiHull{};
	for (const auto& v: vhull) {
		h.push_back(v.rotate(t));
	}
	return h;
}

