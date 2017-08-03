#pragma once
#include <string>

int const WINDOW_WIDTH = 1280;
int const WINDOW_HEIGHT = 720;

int const CAMERA_SPEED = 250;
int const CAMERA_MARGIN = 30;

int const FRAME_RATE_CAP = 120;

std::string const TEXTURE_ID_PATH = "assets/IDs.txt";

namespace HERO {
	int const SPRITE_WIDTH = 64;
	int const SPRITE_HEIGHT = 64;
	int const SPRITESHEET_WIDTH = 20;

	int const COLLISION_WIDTH = 56;
	int const COLLISION_HEIGHT = 61;
	int const COLLISION_SPRITE_MARGIN_X = 4;
	int const COLLISION_SPRITE_MARGIN_Y = 3;

	int const BASE_SPEED = 300;
	float const INVULN_TIME = 0.5f;

	float const ATTACK_1_TIME = 0.3f;
	int const ATTACK_1_WIDTH = 150;
	int const ATTACK_1_HEIGHT = 64;
	int const ATTACK_1_DAMAGE = 5;

	float const ATTACK_2_TIME = 0.2f;
	int const DASH_DISTANCE = 400;

	float const COMBO_1_TIME = 0.5f;
	int const COMBO1_WIDTH = 192;
	int const COMBO1_HEIGHT = 192;
	int const COMBO1_MARGIN_X = 64;
	int const COMBO1_MARGIN_Y = 64;
	int const COMBO1_DAMAGE = 5;
}

namespace ENEMY {
	int const SPRITE_WIDTH = 64;
	int const SPRITE_HEIGHT = 64;
	int const SPRITESHEET_WIDTH = 1;

	int const COLLISION_WIDTH = 64;
	int const COLLISION_HEIGHT = 64;
	int const COLLISION_SPRITE_MARGIN_X = 0;
	int const COLLISION_SPRITE_MARGIN_Y = 0;

	int const SPEED = 200;
	float const IDLE_TIME = 1.5f;
}

namespace CHARGE_ENEMY {
	int const SPRITE_WIDTH = 64;
	int const SPRITE_HEIGHT = 64;
	int const SPRITESHEET_WIDTH = 1;

	int const COLLISION_WIDTH = 64;
	int const COLLISION_HEIGHT = 64;
	int const COLLISION_SPRITE_MARGIN_X = 0;
	int const COLLISION_SPRITE_MARGIN_Y = 0;

	int const CHARGESPEED = 450;
	float const CHARGE_TIME = 1.5f;
}

namespace TILE_ID {
	std::string const BASIC = "TILE001";
}

namespace SPRITE_ID {
	std::string const MENU_BACKGROUND = "MENU001";
	std::string const MENU_TITLE = "MENU002";

	std::string const HERO = "HERO001";
	std::string const HERO_ATTACK1 = "ATTK001";

	std::string const ENEMY = "ENMY001";
	std::string const CHARGE_ENEMY = "ENMY002";
}

// temporary settings
bool const MUTE = true;