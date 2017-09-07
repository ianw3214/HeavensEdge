#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "enemy.h"

#include "constants.h"
#include "collision.h"
#include "player.h"
#include "hero.h"

#include <iostream>

class Boss : public Enemy {

	// custom struct for projectiles
	struct Projectile {
		Sprite * sprite;
		int x, y;
		Rectangle * collisionBox;
		/* Directions:
		0 - up
		1 - topright
		2 - right
		3 - downright
		4 - down
		5 - downleft
		6 - left
		7 - topleft
		*/
		int direction;
		Projectile() : sprite(new Sprite(SPRITE_ID::BOSS_PROJECTILE, 0, 0, 24, 24)), 
			collisionBox(new Rectangle(0, 0, 24, 24)), direction(0) {}
		Projectile(int _x, int _y, int _d) 
			: sprite(new Sprite(SPRITE_ID::BOSS_PROJECTILE, 0, 0, 24, 24)),
			x(_x), y(_y), collisionBox(new Rectangle(_x, _y, 24, 24)), direction(_d) {}
	};

public:

	Boss();
	Boss(int, int);
	virtual ~Boss() {};

	void update(float);
	void render(SDL_Renderer*, SDL_Rect);

private:

	void init(int, int);

	std::vector<Projectile*> projectiles;

	float attackTimer;
	void projectileAttack();
	void bigProjectileAttack();

	Hero * hero;

};