#include "stage.h"

Stage::~Stage()
{
	free();
}

void Stage::free(void)
{
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->free();
		objects[i].reset();
	}
	objects.clear();
}

void Stage::addPObject(std::shared_ptr<PObject> d)
{
	if (d) {
		objects.push_back(d);
	}
}

void Stage::update(void)
{
	PObject::update();
	for (auto it = objects.begin(); it != objects.end(); it++) {
		(*it)->update();
	}

	// const auto& s = shape;
	// auto it = std::remove_if(objects.begin(), objects.end(),
	// 		[s](std::shared_ptr<PObject> o)
	// 		{
	// 		auto t = o->shape;
	// 		if (t) {
	// 		// t->translate(o->x, o->y);
	// 		fprintf(stderr, "<<OUT? (%f, %f)>>\r", o->x, o->y);
	// 		return !s->intersects(*t);
	// 		}
	// 		return false;
	// 		});
	// objects.erase(it, objects.end());
}

void Stage::render(double xoff, double yoff) const
{
	// Render the stage's texture.
	if (texture != nullptr) {
		texture->render(
				x + xoff - (texture->swidth()  / 2),
				y + yoff - (texture->sheight() / 2));
	}

	shape->renderTexture();

	// Render the stage's objects.
	for (size_t i = 0; i < objects.size(); i++) {
		// objects[i]->render(x + xoff, y + yoff);
		objects[i]->render();
	}
}

void Stage::map(std::function<void(std::shared_ptr<PObject>,
			std::shared_ptr<Stage>, size_t)> f)
{
	for (size_t i = 0; i < objects.size(); i++) {
		f(objects[i], std::dynamic_pointer_cast<Stage>(objects[i]), i);
	}
}

