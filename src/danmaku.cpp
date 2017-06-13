#include "danmaku.h"

Danmaku::~Danmaku()
{
	free();
}

void Danmaku::free(void)
{
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->free();
		objects[i].reset();
	}
	objects.clear();
}

void Danmaku::addPObject(std::shared_ptr<PObject> d)
{
	objects.push_back(d);
}

void Danmaku::update(void)
{
	PObject::update();
	for (auto it = objects.begin(); it != objects.end(); it++) {
		(*it)->update();
	}

	const auto& s = shape;
	auto it = std::remove_if(objects.begin(), objects.end(),
			[s](std::shared_ptr<PObject> o)
			{
			return (o->shape != nullptr) ? !s->intersects(*(o->shape)) : false;
			});
	objects.erase(it, objects.end());
}

bool Danmaku::intersects(const Shape& s) const
{
	for (const auto& o: objects) {
		if (o->intersects(s)) {
			return true;
		}
	}

	return false;
}

void Danmaku::render(double xoff, double yoff) const
{
	// Render the danmaku's texture.
	if (texture != nullptr) {
		texture->render(
				x + xoff - (texture->swidth()  / 2),
				y + yoff - (texture->sheight() / 2));
	}

	// Render the danmaku's shape.
	shape->renderTexture(x + xoff, y + yoff);

	// Render the danmaku's objects.
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->render(x + xoff, y + yoff);
	}
}

// void Danmaku::translate(double dx, double dy)
// {
// 	for (size_t i = 0; i < objects.size(); i++) {
// 		objects[i]->translate(dx, dy);
// 	}
// }

void Danmaku::map(std::function<void(std::shared_ptr<PObject>,
			std::shared_ptr<Danmaku>, size_t)> f)
{
	for (size_t i = 0; i < objects.size(); i++) {
		f(objects[i], std::dynamic_pointer_cast<Danmaku>(objects[i]), i);
	}
}

