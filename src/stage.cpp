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
	for (auto it = objects.begin(); it != objects.end();) {
		(*it)->update();
		const auto& t = (*it)->shape;
		if (t) {
            t->translate((*it)->x, (*it)->y);
			bool onscreen = shape->intersects(*t);
			if (!onscreen) {
				it = objects.erase(it);
				continue;
			}
		}
		it++;
	}
}

bool Stage::intersects(const Shape& ps) const
{
	for (auto it = objects.begin(); it != objects.end(); it++) {
		if ((*it)->shape) {
            // Such elegance, much wow.
            (*it)->shape->translate((*it)->x, (*it)->y);
			if ((*it)->shape->intersects(ps)) {
				return true;
			}
		}
	}
	return false;
}

void Stage::render(double xoff, double yoff) const
{
	// Render the stage's texture.
	if (texture != nullptr) {
		texture->render(
				x + xoff - (texture->swidth()  / 2),
				y + yoff - (texture->sheight() / 2));
	}

	// shape->renderTexture();

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

