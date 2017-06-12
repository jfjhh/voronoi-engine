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
	d->translate(x, y);
	objects.push_back(d);
}

void Stage::update(void)
{
	PObject::update();
	for (auto it = objects.begin(); it != objects.end(); it++) {
		(*it)->update();
	}

	auto it = std::remove_if(objects.begin(), objects.end(),
			[](std::shared_ptr<PObject> o)
			{
			SDL_Rect field = {
			0,            0,
			(int) SCREEN_WIDTH, (int) SCREEN_HEIGHT,
			};
			Hitbox f;
			f.add(field);
			return !f.intersects(o->getHitbox());
			});
	objects.erase(it, objects.end());
}

void Stage::render(double xoff, double yoff) const
{
	// Render the stage's texture.
	if (texture != nullptr) {
		texture->render(
				x + xoff - (texture->swidth()  / 2),
				y + yoff - (texture->sheight() / 2));
	}

	// Render the stage's hitbox.
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0xff, 0xff, 0xff);
	Hitbox h = hitbox;
	h.translate(x + xoff, y + yoff);
	h.render();

	// Render the stage's objects.
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->render(x + xoff, y + yoff);
	}
}

void Stage::map(std::function<void(std::shared_ptr<PObject>,
			std::shared_ptr<Stage>, size_t)> f)
{
	for (size_t i = 0; i < objects.size(); i++) {
		f(objects[i], std::dynamic_pointer_cast<Stage>(objects[i]), i);
	}
}

