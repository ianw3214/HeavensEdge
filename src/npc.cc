#include "npc.h"

NPC::NPC() : Creature(0, 0, 10, 4), dialogue({}) {
	init();
}

NPC::NPC(int x, int y) : Creature(x, y, 10, 4), dialogue({}) {
	init();
}

NPC::NPC(int x, int y, std::vector<std::string> d) : Creature(x, y, 10, 4) , dialogue(d) {
	init();
}

// getter/setter methods
std::vector<std::string> NPC::getDialogue() const { return dialogue; }

void NPC::update(float delta) {
	// update collision rectangle
	collisionBox->x = x + collisionMarginX;
	collisionBox->y = y + collisionMarginY;
	// update sprite
	sprite->update(delta);
	sprite->setPos(x, y);
}

void NPC::render(SDL_Surface* display, SDL_Rect camera) {
	sprite->render(display, camera);
}

void NPC::init() {
	sprite = new AnimatedSprite("assets/testNPC.png", 64, 64, 1, false);
	sprite->setAnimationData({ 1 });
	// set the default collision rectangle
	collisionBox = new Rectangle(x, y, 64, 64);
}