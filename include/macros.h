#pragma once

//window dimensions:
const int WINDOW_WIDTH = 1280,
		  WINDOW_HEIGHT = 720;

const float TILE_SIZE = 48.f;
const float GAP = 1.f;
const unsigned int FPS = 60;

const float SPRINGBOARD_SPEED = -624.f;

//level file symbols:
enum Symbol {
	orange = 'O',
	rollingEnemy = 'r',
	flyingMonster = 'F',
	jellyfish = 'j',
	spike = 'K',
	carnivorous = 't',
	cannon = 'T',
	escalator = 'E',
	grass = '^',
	grassLeft = 'G',
	grassRight = 'g',
	flatGrass = '*',
	flatGrassLeft = '0',
	flatGrassRight = '1',
	stones = '=',
	stonesLeft = 'S',
	stonesRight = 's',
	soil = '-',
	soilLeft = 'A',
	soilRight = 'a',
	soilCornerLeft = 'C',
	soilCornerRight = 'c',
	soilBottom = 'B',
	soilHoles = 'H',
	coin = '$',
	wood = 'W',
	silverBrick = '2',
	goldBrick = '3',
	redBrick = '4',
	woodBrick = '5',
	smallBrick = '6',
	largeBrick = '7',
	surpriseBox = '8',
	water = 'w',
	waterBottom = '~',
	waterCornerLeft = 'L',
	waterCornerRight = 'R',
	springBoard = 'M',
	door = 'D',
	bubble = 'o'
};

//animation frames:
const int PLAYER_WALK_FRAMES = 4;
const int ORANGE_WALK_FRAMES = 20;
const int ROLLING_ENEMY_FRAMES = 20;
const int JELLYFISH_FRAMES = 3;
const int FLYING_MONSTER_FRAMES = 18;
const int COIN_FRAMES = 6;
const int SPRING_BOARD_FRAMES = 4;
const int BONE_FRAMES = 8;
const int DISPOSE_FRAMES = 8;

const int BACKGROUND_FRAMES = 10;