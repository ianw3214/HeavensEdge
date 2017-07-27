#include "npc.h"

NPC::NPC(SDL_Renderer* renderer) : Creature(0, 0, 10, 4), dialogue({}) {
	init("assets/testNPC.png", renderer);
}

NPC::NPC(int x, int y, SDL_Renderer* renderer) : Creature(x, y, 10, 4), dialogue({}) {
	init("assets/testNPC.png", renderer);
}

NPC::NPC(int x, int y, std::vector<std::string> d, SDL_Renderer* renderer) : Creature(x, y, 10, 4) , dialogue(d) {
	init("assets/testNPC.png", renderer);
}

NPC::NPC(int x, int y, std::vector<std::string> d, std::string path, SDL_Renderer* renderer) : Creature(x, y, 10, 4), dialogue(d) {
	init(path, renderer);
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

void NPC::render(SDL_Renderer* renderer, SDL_Rect camera) {
	sprite->render(renderer, camera);
}

void NPC::init(std::string path, SDL_Renderer* renderer) {
	sprite = new AnimatedSprite(path, 64, 64, 1, false, renderer);
	sprite->setAnimationData({ 1 });
	// set the default collision rectangle
	collisionBox = new Rectangle(x, y, 64, 64);
}