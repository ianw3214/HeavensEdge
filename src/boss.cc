#include "boss.h"

Boss::Boss() {
	init(0, 0);
}

Boss::Boss(int _x, int _y) {
	init(_x, _y);
}

void Boss::update(float delta) {
	// update basic properties of the creature
	sprite->update(delta);
	sprite->setPos(x, y);
	collisionBox->x = x + collisionMarginX;
	collisionBox->y = y + collisionMarginY;
	// remove the boss if it is dead
	if (health <= 0) REMOVE = true;
	// update movement
	if (idleTimer > 0.0f) {
		idleTimer -= delta;
		if (idleTimer <= 0.0f) idleTimer = 0.0f;
	}
	// update projectiles
	for (int i = projectiles.size() - 1; i >= 0; i--) {
		Projectile * p = projectiles[i];
		int speed = 600 * delta;
		int d = p->direction;
		int newX = p->x, newY = p->y;
		if (d == 0 || d == 1 || d == 7)	newY -= speed;
		if (d == 1 || d == 2 || d == 3)	newX += speed;
		if (d == 3 || d == 4 || d == 5)	newY += speed;
		if (d == 5 || d == 6 || d == 7)	newX -= speed;
		// remove the projectile if it is out of bounds
		if (newX < -2000 || newX > 5000 || newY < -2000 || newY > 5000) {
			Projectile * temp = p;
			projectiles.erase(projectiles.begin() + i);
			delete temp;
			continue;
		}
		// otherwise, update the position of the projectiles
		p->x = newX, p->y = newY;
		p->sprite->setPos(newX, newY);
	}
	// attack if the timer counts down
	if (attackTimer <= 0.0f) {
		attackTimer = 1.0f;
		// randomly use a big attack instead
		if (rand() % 5 < 1) 
			bigProjectileAttack();
		else
			projectileAttack();
		
	}
	else {
		attackTimer -= delta;
	}
	// update the sprite to play the correct animation
	sprite->playAnimation(0);
}

void Boss::render(SDL_Renderer* renderer, SDL_Rect camera) {
	sprite->render(renderer, camera);
	// render projectiles
	for (const Projectile * p : projectiles) {
		p->sprite->render(renderer, camera);
	}
}

void Boss::init(int _x, int _y) {
	sprite = new AnimatedSprite(SPRITE_ID::BOSS, 128, 128, 1, false);
	sprite->setAnimationData({ 1 });
	collisionBox = new Rectangle({ _x, _y, 128, 128 });
	collisionMarginX = 0;
	collisionMarginY = 0;
	x = _x, y = _y;
	health = 50;
	type = 3;
	idleTimer = 0.0f;
	attackTimer = 0.0f;
	// look for the hero from the entity list
	for (unsigned int i = 0; i < Creature::entityList->size(); i++) {
		if (entityList->at(i)->getType() == 2) {
			Player * temp = dynamic_cast<Player*>(entityList->at(i));
			hero = dynamic_cast<Hero*>(temp->getHero());
		}
	}
	if (!hero) std::cout << "ERROR: Could not find a hero entity." << std::endl;
}

void Boss::projectileAttack() {
	int key = rand() % 7;
	Projectile * temp = new Projectile(x + 64, y + 64, key);
	projectiles.push_back(temp);
}

void Boss::bigProjectileAttack() {
	for (int i = 0; i < 8; i++) {
		Projectile * temp = new Projectile(x + 64, y + 64, i);
		projectiles.push_back(temp);
	}
}