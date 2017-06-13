#include "bulletdata.h"

static BulletData none = {
	BulletType::NONE,
	"",
	nullptr,
	nullptr,
};

static BulletData point = {
	BulletType::POINT,
	"",
	std::make_shared<Point>(),
	nullptr,
};

static BulletData circle = {
	BulletType::CIRCLE,
	"circle.png",
	std::make_shared<Circle>(5.0),
	std::make_shared<PTexture>(),
};

static BulletData rect = {
	BulletType::RECT,
	"rect.png",
	std::make_shared<Rectangle>(10.0),
	std::make_shared<PTexture>(),
};

std::array<BulletData, BULLET_DATA_MAX> BULLETS = {
	none,
	point,
	circle,
	rect,
};

