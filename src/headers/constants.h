#pragma once
#include <string>
#include <vector>

// basic constants
int const WINDOW_WIDTH = 1280;
int const WINDOW_HEIGHT = 720;

int const CAMERA_SPEED = 250;
int const CAMERA_MARGIN = 30;

int const FRAME_RATE_CAP = 120;

std::string const TEXTURE_ID_PATH = "assets/IDs.txt";

// menu constants
std::vector<std::pair<int, int>> const ratios = {
	std::make_pair(1280, 720),
	std::make_pair(720, 480),
	std::make_pair(1920, 1080)
};

std::vector<int> const volumes = {
	0,
	16,
	32,
	64,
	128
};

std::vector<int> const OPTION_SELECT_HEIGHTS = {
	150,
	235,
	320,
	410,
	560
};

int const TITLE_WIDTH = 1000;
int const TITLE_HEIGHT = 200;
int const OPTION_WIDTH = 400;
int const OPTION_HEIGHT = 80;

namespace MENU_SETTINGS {
	int const TITLE_WIDTH = 360;
	int const TITLE_HEIGHT = 80;
	int const TITLE_MARGIN_TOP = 40;
	int const TITLE_MARGIN_LEFT = 40;
}

int const TWEEN_TIME = 350;

// hero constants
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
	int const COMBO1_MARGIN = 64;
}

// enemy constants
namespace ENEMY {
	int const SPRITE_WIDTH = 64;
	int const SPRITE_HEIGHT = 64;
	int const SPRITESHEET_WIDTH = 2;

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
	int const SPRITESHEET_WIDTH = 14;

	int const COLLISION_WIDTH = 64;
	int const COLLISION_HEIGHT = 64;
	int const COLLISION_SPRITE_MARGIN_X = 0;
	int const COLLISION_SPRITE_MARGIN_Y = 0;

	int const CHARGESPEED = 450;
	float const CHARGE_TIME = 1.5f;
}

// id constants
namespace TILE_ID {
	std::string const BASIC = "TILE001";
}

namespace SPRITE_ID {
	std::string const MENU_BACKGROUND = "MENU001";
	std::string const MENU_TITLE = "MENU002";
	std::string const MENU_PLAY = "MENU003";
	std::string const MENU_SETTINGS = "MENU004";
	std::string const MENU_QUIT = "MENU005";
	std::string const MENU_SELECT = "MENU006";
	std::string const OPTION_OVERLAY = "MENU007";
	std::string const OPTION_SELECT = "MENU008";

	std::string const HERO = "HERO001";
	std::string const SHADOW = "HERO002";
	std::string const HERO_ATTACK1 = "ATTK001";
	std::string const HERO_COMBO1 = "COMB001";

	std::string const ENEMY = "ENMY001";
	std::string const CHARGE_ENEMY = "ENMY002";

	std::string const DEATH_MENU = "DEAD001";
}

namespace PARTICLE_ID{
	std::string const LEAF = "PART001";
}