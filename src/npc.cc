#include "npc.h"

NPC::NPC() : Creature(0, 0, 10, 4), dialogue({}) {
	init("assets/testNPC.png");
}

NPC::NPC(int x, int y) : Creature(x, y, 10, 4), dialogue({}) {
	init("assets/testNPC.png");
}

NPC::NPC(int x, int y, std::vector<std::string> d) : Creature(x, y, 10, 4) , dialogue(d) {
	init("assets/testNPC.png");
}

NPC::NPC(int x, int y, std::vector<std::string> d, std::string path) : Creature(x, y, 10, 4), dialogue(d) {
	init(path);
}

// getter/setter methods
std::vector<std::string> NPC::getDialogue() const { return dialogue; }

void NPC::update(float delta) {
	// update the shadow
	shadow->setPos(x + 8, y + 56);
	// update collision rectangle
	collisionBox->x = x + collisionMarginX;
	collisionBox->y = y + collisionMarginY;
	// update sprite
	sprite->update(delta);
	sprite->setPos(x, y);
}

void NPC::render(SDL_Renderer* renderer, SDL_Rect camera) {
	// render the shadow first
	shadow->render(renderer, camera);
	sprite->render(renderer, camera);
}

void NPC::init(std::string path) {
	sprite = new AnimatedSprite(path, 64, 64, 20, false);
	// assume all NPCs have 20 frame loops for now
	// TODO: load animation data from a central source
	sprite->setAnimationData({ 20 });
	// set the default collision rectangle
	collisionBox = new Rectangle(x, y, 64, 64);
	// load the shadow sprite, assume all NPCs are 64 by 64 for now
	shadow = new Sprite(SPRITE_ID::NPC_SHADOW, 0, 0, 48, 16);
}