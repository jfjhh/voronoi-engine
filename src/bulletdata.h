/**
 * Bullet Data.
 * Alex Striff.
 */

#ifndef BULLETDATA_H
#define BULLETDATA_H

#include <memory>
#include <array>
#include "commont.h"
#include "ptexture.h"
#include "geometry.h"

#ifndef SPRITE_FILE_MAX
#define SPRITE_FILE_MAX 64
#endif /* SPRITE_FILE_MAX */

#ifndef BULLET_DATA_MAX
#define BULLET_DATA_MAX 4
#endif /* BULLET_DATA_MAX */

/**
 * The bullet types.
 */
enum class BulletType : int {
	NONE = 0,
	POINT,
	CIRCLE,
	RECT,
};
COMMON_VERIFY(BulletType);

/**
 * The bullet data structure.
 */
using BulletData = struct bullet_data_t {
	BulletType type;
	char sprite_file[SPRITE_FILE_MAX];
	std::shared_ptr<Shape> shape;
	std::shared_ptr<PTexture> texture;
};
COMMON_VERIFY(BulletData);

extern std::array<BulletData, BULLET_DATA_MAX> BULLETS;

#endif /* BULLETDATA_H */

