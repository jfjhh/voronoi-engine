#include "shape.h"

Shape::Shape(coord tw):
	x(0.0), y(0.0)
{
	t = 0.0;
	center = {0.0, 0.0, tw / 2.0};
	vhull.push_back(center);
	shapeTexture = std::make_shared<PTexture>();
}

Shape::Shape(coord tw, coord th): Shape(std::max(tw, th)) {}

void Shape::translate(coord x, coord y)
{
	this->x = x;
	this->y = y;
}

void Shape::render(void) const
{
	fputs("<SHAPE native point render>\n", stderr);
	for (const auto& v: chull) {
		filledCircleRGBA(gRenderer, v.x, v.y, 5, 255, 255, 255, 255);
	}
	for (const auto& v: vhull) {
		filledCircleRGBA(gRenderer, v.x, v.y, v.r, 255, 255, 255, 255);
	}
}

void Shape::renderTargeted(void)
{
	if (!textureOK) return;
	fprintf(stderr, "<Rendering a %s to shape internal target texture>\n",
			typeid(*this).name() + 1);
	SDL_Texture *old = shapeTexture->setRenderTarget();
	SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0x00);
	// SDL_SetRenderDrawColor(gRenderer, 0xff, 0x00, 0xff, 0x44);
	SDL_RenderClear(gRenderer);

	render();

	SDL_SetRenderTarget(gRenderer, old);
}

void Shape::renderTexture(coord x, coord y, coord add_rot)
{
	if (textureOK) {
		shapeTexture->render(
				x + center.x, y + center.y,
				NULL, t + add_rot, NULL, SDL_FLIP_NONE);
	}
}

bool Shape::setTextureWidth(int tw)
{
	textureSide = tw;
	return renewTexture();
}

bool Shape::renewTexture(void)
{
	if (!gRenderer) return false;
	fprintf(stderr,"<Renewing a %s's\ttexture (%3d) ... ",
			typeid(*this).name() + 1,
			textureSide);
	textureOK = shapeTexture->createBlank(
			(int) textureSide, (int) textureSide, SDL_TEXTUREACCESS_TARGET);
	fputs(textureOK ? "Done!>\t" : "Renderer Not Ready!>\n", stderr);
	renderTargeted();
	return textureOK;
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

Range Shape::projectOn(coord axis, Vertex v) const
{
	auto vt = atan2(y, x);
	auto on = vt > axis ? vt + axis : axis - vt;
	// fprintf(stderr, "ProjON: %f <=> %f", axis, on);
	return project(on, v);
}

Range Shape::project(coord on, Vertex v) const
{
	auto r = inverse_range;

	for (const auto& c: chull) {
		r.update(c.distanceTo({x + v.y, y + v.x}) * cos(on));
	}

	return r;
}

void Shape::setVCenter(const VoronoiVertex& v)
{
	center = v;
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

