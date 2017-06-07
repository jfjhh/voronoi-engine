/**
 * Bullet Data.
 * Alex Striff.
 */

#ifndef BULLETDATA_H
#define BULLETDATA_H

#include <memory>
#include "ptexture.h"
#include "hitbox.h"

#ifndef SPRITE_FILE_MAX
#define SPRITE_FILE_MAX	64
#endif /* SPRITE_FILE_MAX */

/**
 * The bullet types.
 */
enum class BulletType : int {
	NONE = 0,
	CIRCLE,
	RECT,
};

/**
 * The bullet data structure.
 */
typedef struct bullet_data_t {
	BulletType type;
	char       sprite_file[SPRITE_FILE_MAX];
	Hitbox     hitbox;
	std::shared_ptr<PTexture> texture;
} BulletData;

extern BulletData BULLETS[];
extern size_t     BULLETS_LENGTH;

#endif /* BULLETDATA_H */


