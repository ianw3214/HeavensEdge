#pragma once
#include <string>

int const WINDOW_WIDTH = 1280;
int const WINDOW_HEIGHT = 720;

int const CAMERA_SPEED = 2;
int const CAMERA_MARGIN = 30;

int const FRAME_RATE_CAP = 120;

namespace HERO {
	int const BASE_SPEED = 300;
	int const COLLISION_WIDTH = 56;
	int const COLLISION_HEIGHT = 61;
	int const COLLISION_SPRITE_MARGIN_X = 4;
	int const COLLISION_SPRITE_MARGIN_Y = 3;
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

namespace CHARGE_ENEMY {
	int const CHARGESPEED = 450;
	float const CHARGE_TIME = 1.5f;
}

namespace SPRITE_PATH {
	std::string const MENU_BACKGROUND = "assets/menu/menu_bg.png";

	std::string const HERO = "assets/hero/hero.png";
	std::string const HERO_ATTACK1 = "assets/hero/hero_attack1.png";

	std::string const ENEMY = "assets/enemies/enemy.png";
	std::string const CHARGE_ENEMY = "assets/enemies/ChargeEnemy.png";
}

// temporary settings
bool const MUTE = true;