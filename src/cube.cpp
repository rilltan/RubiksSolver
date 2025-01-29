#include "cube.h"
#include <functional>
#include <iostream>
#include <stack>
#include <thread>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <iomanip>

const std::string MoveStrings[] = { "L2", "R2", "F2", "B2", "U2", "D2", "L", "R", "F", "B", "U", "D", "L'", "R'", "F'", "B'", "U'", "D'", "NOTHING" };
const Face cubies[8][3] = {
	{UP, LEFT, FRONT},
	{UP, BACK, LEFT},
	{UP, FRONT, RIGHT},
	{UP, RIGHT, BACK},
	{DOWN, FRONT, LEFT},
	{DOWN, LEFT, BACK},
	{DOWN, RIGHT, FRONT},
	{DOWN, BACK, RIGHT}
};

Cube executeMove(Cube cube, Move move) {
	switch (move) {
	case U: {
		cube[UP] = cube[UP] >> 8 | cube[UP] << 24;
		uint32_t front = cube[FRONT];
		cube[FRONT] = (cube[FRONT] & 0x000FFFFF) | (cube[RIGHT] & 0xFFF00000);
		cube[RIGHT] = (cube[RIGHT] & 0x000FFFFF) | (cube[BACK] & 0xFFF00000);
		cube[BACK] = (cube[BACK] & 0x000FFFFF) | (cube[LEFT] & 0xFFF00000);
		cube[LEFT] = (cube[LEFT] & 0x000FFFFF) | (front & 0xFFF00000);
	} break;
	case U2: {
		cube[UP] = cube[UP] >> 8 | cube[UP] << 24;
		uint32_t front = cube[FRONT];
		cube[FRONT] = (cube[FRONT] & 0x000FFFFF) | (cube[RIGHT] & 0xFFF00000);
		cube[RIGHT] = (cube[RIGHT] & 0x000FFFFF) | (cube[BACK] & 0xFFF00000);
		cube[BACK] = (cube[BACK] & 0x000FFFFF) | (cube[LEFT] & 0xFFF00000);
		cube[LEFT] = (cube[LEFT] & 0x000FFFFF) | (front & 0xFFF00000);

		cube[UP] = cube[UP] >> 8 | cube[UP] << 24;
		front = cube[FRONT];
		cube[FRONT] = (cube[FRONT] & 0x000FFFFF) | (cube[RIGHT] & 0xFFF00000);
		cube[RIGHT] = (cube[RIGHT] & 0x000FFFFF) | (cube[BACK] & 0xFFF00000);
		cube[BACK] = (cube[BACK] & 0x000FFFFF) | (cube[LEFT] & 0xFFF00000);
		cube[LEFT] = (cube[LEFT] & 0x000FFFFF) | (front & 0xFFF00000);
	} break;
	case U3: {
		cube[UP] = cube[UP] >> 8 | cube[UP] << 24;
		uint32_t front = cube[FRONT];
		cube[FRONT] = (cube[FRONT] & 0x000FFFFF) | (cube[RIGHT] & 0xFFF00000);
		cube[RIGHT] = (cube[RIGHT] & 0x000FFFFF) | (cube[BACK] & 0xFFF00000);
		cube[BACK] = (cube[BACK] & 0x000FFFFF) | (cube[LEFT] & 0xFFF00000);
		cube[LEFT] = (cube[LEFT] & 0x000FFFFF) | (front & 0xFFF00000);

		cube[UP] = cube[UP] >> 8 | cube[UP] << 24;
		front = cube[FRONT];
		cube[FRONT] = (cube[FRONT] & 0x000FFFFF) | (cube[RIGHT] & 0xFFF00000);
		cube[RIGHT] = (cube[RIGHT] & 0x000FFFFF) | (cube[BACK] & 0xFFF00000);
		cube[BACK] = (cube[BACK] & 0x000FFFFF) | (cube[LEFT] & 0xFFF00000);
		cube[LEFT] = (cube[LEFT] & 0x000FFFFF) | (front & 0xFFF00000);

		cube[UP] = cube[UP] >> 8 | cube[UP] << 24;
		front = cube[FRONT];
		cube[FRONT] = (cube[FRONT] & 0x000FFFFF) | (cube[RIGHT] & 0xFFF00000);
		cube[RIGHT] = (cube[RIGHT] & 0x000FFFFF) | (cube[BACK] & 0xFFF00000);
		cube[BACK] = (cube[BACK] & 0x000FFFFF) | (cube[LEFT] & 0xFFF00000);
		cube[LEFT] = (cube[LEFT] & 0x000FFFFF) | (front & 0xFFF00000);
	} break;
	case D: {
		cube[DOWN] = cube[DOWN] >> 8 | cube[DOWN] << 24;
		uint32_t front = cube[FRONT];
		cube[FRONT] = (cube[FRONT] & 0xFFFF000F) | (cube[LEFT] & 0x0000FFF0);
		cube[LEFT] = (cube[LEFT] & 0xFFFF000F) | (cube[BACK] & 0x0000FFF0);
		cube[BACK] = (cube[BACK] & 0xFFFF000F) | (cube[RIGHT] & 0x0000FFF0);
		cube[RIGHT] = (cube[RIGHT] & 0xFFFF000F) | (front & 0x0000FFF0);
	} break;
	case D2: {
		cube[DOWN] = cube[DOWN] >> 8 | cube[DOWN] << 24;
		uint32_t front = cube[FRONT];
		cube[FRONT] = (cube[FRONT] & 0xFFFF000F) | (cube[LEFT] & 0x0000FFF0);
		cube[LEFT] = (cube[LEFT] & 0xFFFF000F) | (cube[BACK] & 0x0000FFF0);
		cube[BACK] = (cube[BACK] & 0xFFFF000F) | (cube[RIGHT] & 0x0000FFF0);
		cube[RIGHT] = (cube[RIGHT] & 0xFFFF000F) | (front & 0x0000FFF0);

		cube[DOWN] = cube[DOWN] >> 8 | cube[DOWN] << 24;
		front = cube[FRONT];
		cube[FRONT] = (cube[FRONT] & 0xFFFF000F) | (cube[LEFT] & 0x0000FFF0);
		cube[LEFT] = (cube[LEFT] & 0xFFFF000F) | (cube[BACK] & 0x0000FFF0);
		cube[BACK] = (cube[BACK] & 0xFFFF000F) | (cube[RIGHT] & 0x0000FFF0);
		cube[RIGHT] = (cube[RIGHT] & 0xFFFF000F) | (front & 0x0000FFF0);
	} break;
	case D3: {
		cube[DOWN] = cube[DOWN] >> 8 | cube[DOWN] << 24;
		uint32_t front = cube[FRONT];
		cube[FRONT] = (cube[FRONT] & 0xFFFF000F) | (cube[LEFT] & 0x0000FFF0);
		cube[LEFT] = (cube[LEFT] & 0xFFFF000F) | (cube[BACK] & 0x0000FFF0);
		cube[BACK] = (cube[BACK] & 0xFFFF000F) | (cube[RIGHT] & 0x0000FFF0);
		cube[RIGHT] = (cube[RIGHT] & 0xFFFF000F) | (front & 0x0000FFF0);
		
		cube[DOWN] = cube[DOWN] >> 8 | cube[DOWN] << 24;
		front = cube[FRONT];
		cube[FRONT] = (cube[FRONT] & 0xFFFF000F) | (cube[LEFT] & 0x0000FFF0);
		cube[LEFT] = (cube[LEFT] & 0xFFFF000F) | (cube[BACK] & 0x0000FFF0);
		cube[BACK] = (cube[BACK] & 0xFFFF000F) | (cube[RIGHT] & 0x0000FFF0);
		cube[RIGHT] = (cube[RIGHT] & 0xFFFF000F) | (front & 0x0000FFF0);

		cube[DOWN] = cube[DOWN] >> 8 | cube[DOWN] << 24;
		front = cube[FRONT];
		cube[FRONT] = (cube[FRONT] & 0xFFFF000F) | (cube[LEFT] & 0x0000FFF0);
		cube[LEFT] = (cube[LEFT] & 0xFFFF000F) | (cube[BACK] & 0x0000FFF0);
		cube[BACK] = (cube[BACK] & 0xFFFF000F) | (cube[RIGHT] & 0x0000FFF0);
		cube[RIGHT] = (cube[RIGHT] & 0xFFFF000F) | (front & 0x0000FFF0);
	} break;
	case L: {
		cube[LEFT] = cube[LEFT] >> 8 | cube[LEFT] << 24;
		uint32_t front = cube[FRONT];
		cube[FRONT] = (cube[FRONT] & 0x0FFFFF00) | (cube[UP] & 0xF00000FF);
		cube[UP] = (cube[UP] & 0x0FFFFF00) | (cube[BACK] & 0x00FF0000) >> 16 | (cube[BACK] & 0x0000F000) << 16;
		cube[BACK] = (cube[BACK] & 0xFF000FFF) | (cube[DOWN] & 0xF0000000) >> 16 | (cube[DOWN] & 0x000000FF) << 16;
		cube[DOWN] = (cube[DOWN] & 0x0FFFFF00) | (front & 0xF00000FF);
	} break;
	case L2: {
		cube[LEFT] = cube[LEFT] >> 8 | cube[LEFT] << 24;
		uint32_t front = cube[FRONT];
		cube[FRONT] = (cube[FRONT] & 0x0FFFFF00) | (cube[UP] & 0xF00000FF);
		cube[UP] = (cube[UP] & 0x0FFFFF00) | (cube[BACK] & 0x00FF0000) >> 16 | (cube[BACK] & 0x0000F000) << 16;
		cube[BACK] = (cube[BACK] & 0xFF000FFF) | (cube[DOWN] & 0xF0000000) >> 16 | (cube[DOWN] & 0x000000FF) << 16;
		cube[DOWN] = (cube[DOWN] & 0x0FFFFF00) | (front & 0xF00000FF);

		cube[LEFT] = cube[LEFT] >> 8 | cube[LEFT] << 24;
		front = cube[FRONT];
		cube[FRONT] = (cube[FRONT] & 0x0FFFFF00) | (cube[UP] & 0xF00000FF);
		cube[UP] = (cube[UP] & 0x0FFFFF00) | (cube[BACK] & 0x00FF0000) >> 16 | (cube[BACK] & 0x0000F000) << 16;
		cube[BACK] = (cube[BACK] & 0xFF000FFF) | (cube[DOWN] & 0xF0000000) >> 16 | (cube[DOWN] & 0x000000FF) << 16;
		cube[DOWN] = (cube[DOWN] & 0x0FFFFF00) | (front & 0xF00000FF);
	} break;
	case L3: {
		cube[LEFT] = cube[LEFT] >> 8 | cube[LEFT] << 24;
		uint32_t front = cube[FRONT];
		cube[FRONT] = (cube[FRONT] & 0x0FFFFF00) | (cube[UP] & 0xF00000FF);
		cube[UP] = (cube[UP] & 0x0FFFFF00) | (cube[BACK] & 0x00FF0000) >> 16 | (cube[BACK] & 0x0000F000) << 16;
		cube[BACK] = (cube[BACK] & 0xFF000FFF) | (cube[DOWN] & 0xF0000000) >> 16 | (cube[DOWN] & 0x000000FF) << 16;
		cube[DOWN] = (cube[DOWN] & 0x0FFFFF00) | (front & 0xF00000FF);

		cube[LEFT] = cube[LEFT] >> 8 | cube[LEFT] << 24;
		front = cube[FRONT];
		cube[FRONT] = (cube[FRONT] & 0x0FFFFF00) | (cube[UP] & 0xF00000FF);
		cube[UP] = (cube[UP] & 0x0FFFFF00) | (cube[BACK] & 0x00FF0000) >> 16 | (cube[BACK] & 0x0000F000) << 16;
		cube[BACK] = (cube[BACK] & 0xFF000FFF) | (cube[DOWN] & 0xF0000000) >> 16 | (cube[DOWN] & 0x000000FF) << 16;
		cube[DOWN] = (cube[DOWN] & 0x0FFFFF00) | (front & 0xF00000FF);

		cube[LEFT] = cube[LEFT] >> 8 | cube[LEFT] << 24;
		front = cube[FRONT];
		cube[FRONT] = (cube[FRONT] & 0x0FFFFF00) | (cube[UP] & 0xF00000FF);
		cube[UP] = (cube[UP] & 0x0FFFFF00) | (cube[BACK] & 0x00FF0000) >> 16 | (cube[BACK] & 0x0000F000) << 16;
		cube[BACK] = (cube[BACK] & 0xFF000FFF) | (cube[DOWN] & 0xF0000000) >> 16 | (cube[DOWN] & 0x000000FF) << 16;
		cube[DOWN] = (cube[DOWN] & 0x0FFFFF00) | (front & 0xF00000FF);
	} break;
	case R: {
		cube[RIGHT] = cube[RIGHT] >> 8 | cube[RIGHT] << 24;
		uint32_t front = cube[FRONT];
		cube[FRONT] = (cube[FRONT] & 0xFF000FFF) | (cube[DOWN] & 0x00FFF000);
		cube[DOWN] = (cube[DOWN] & 0xFF000FFF) | (cube[BACK] & 0x000000FF) << 16 | (cube[BACK] & 0xF0000000) >> 16;
		cube[BACK] = (cube[BACK] & 0x0FFFFF00) | (cube[UP] & 0x00FF0000) >> 16 | (cube[UP] & 0x0000F000) << 16;
		cube[UP] = (cube[UP] & 0xFF000FFF) | (front & 0x00FFF000);
	} break;
	case R2: {
		cube[RIGHT] = cube[RIGHT] >> 8 | cube[RIGHT] << 24;
		uint32_t front = cube[FRONT];
		cube[FRONT] = (cube[FRONT] & 0xFF000FFF) | (cube[DOWN] & 0x00FFF000);
		cube[DOWN] = (cube[DOWN] & 0xFF000FFF) | (cube[BACK] & 0x000000FF) << 16 | (cube[BACK] & 0xF0000000) >> 16;
		cube[BACK] = (cube[BACK] & 0x0FFFFF00) | (cube[UP] & 0x00FF0000) >> 16 | (cube[UP] & 0x0000F000) << 16;
		cube[UP] = (cube[UP] & 0xFF000FFF) | (front & 0x00FFF000);

		cube[RIGHT] = cube[RIGHT] >> 8 | cube[RIGHT] << 24;
		front = cube[FRONT];
		cube[FRONT] = (cube[FRONT] & 0xFF000FFF) | (cube[DOWN] & 0x00FFF000);
		cube[DOWN] = (cube[DOWN] & 0xFF000FFF) | (cube[BACK] & 0x000000FF) << 16 | (cube[BACK] & 0xF0000000) >> 16;
		cube[BACK] = (cube[BACK] & 0x0FFFFF00) | (cube[UP] & 0x00FF0000) >> 16 | (cube[UP] & 0x0000F000) << 16;
		cube[UP] = (cube[UP] & 0xFF000FFF) | (front & 0x00FFF000);
	} break;
	case R3: {
		cube[RIGHT] = cube[RIGHT] >> 8 | cube[RIGHT] << 24;
		uint32_t front = cube[FRONT];
		cube[FRONT] = (cube[FRONT] & 0xFF000FFF) | (cube[DOWN] & 0x00FFF000);
		cube[DOWN] = (cube[DOWN] & 0xFF000FFF) | (cube[BACK] & 0x000000FF) << 16 | (cube[BACK] & 0xF0000000) >> 16;
		cube[BACK] = (cube[BACK] & 0x0FFFFF00) | (cube[UP] & 0x00FF0000) >> 16 | (cube[UP] & 0x0000F000) << 16;
		cube[UP] = (cube[UP] & 0xFF000FFF) | (front & 0x00FFF000);

		cube[RIGHT] = cube[RIGHT] >> 8 | cube[RIGHT] << 24;
		front = cube[FRONT];
		cube[FRONT] = (cube[FRONT] & 0xFF000FFF) | (cube[DOWN] & 0x00FFF000);
		cube[DOWN] = (cube[DOWN] & 0xFF000FFF) | (cube[BACK] & 0x000000FF) << 16 | (cube[BACK] & 0xF0000000) >> 16;
		cube[BACK] = (cube[BACK] & 0x0FFFFF00) | (cube[UP] & 0x00FF0000) >> 16 | (cube[UP] & 0x0000F000) << 16;
		cube[UP] = (cube[UP] & 0xFF000FFF) | (front & 0x00FFF000);

		cube[RIGHT] = cube[RIGHT] >> 8 | cube[RIGHT] << 24;
		front = cube[FRONT];
		cube[FRONT] = (cube[FRONT] & 0xFF000FFF) | (cube[DOWN] & 0x00FFF000);
		cube[DOWN] = (cube[DOWN] & 0xFF000FFF) | (cube[BACK] & 0x000000FF) << 16 | (cube[BACK] & 0xF0000000) >> 16;
		cube[BACK] = (cube[BACK] & 0x0FFFFF00) | (cube[UP] & 0x00FF0000) >> 16 | (cube[UP] & 0x0000F000) << 16;
		cube[UP] = (cube[UP] & 0xFF000FFF) | (front & 0x00FFF000);
	} break;
	case F: {
		cube[FRONT] = cube[FRONT] >> 8 | cube[FRONT] << 24;
		uint32_t up = cube[UP];
		cube[UP] = (cube[UP] & 0xFFFF000F) | (cube[LEFT] & 0x00FFF000) >> 8;
		cube[LEFT] = (cube[LEFT] & 0xFF000FFF) | (cube[DOWN] & 0xFFF00000) >> 8;
		cube[DOWN] = (cube[DOWN] & 0x000FFFFF) | (cube[RIGHT] & 0x000000FF) << 24 | (cube[RIGHT] & 0xF0000000) >> 8;
		cube[RIGHT] = (cube[RIGHT] & 0x0FFFFF00) | (up & 0x0000FF00) >> 8 | (up & 0x000000F0) << 24;
	} break;
	case F2: {
		cube[FRONT] = cube[FRONT] >> 8 | cube[FRONT] << 24;
		uint32_t up = cube[UP];
		cube[UP] = (cube[UP] & 0xFFFF000F) | (cube[LEFT] & 0x00FFF000) >> 8;
		cube[LEFT] = (cube[LEFT] & 0xFF000FFF) | (cube[DOWN] & 0xFFF00000) >> 8;
		cube[DOWN] = (cube[DOWN] & 0x000FFFFF) | (cube[RIGHT] & 0x000000FF) << 24 | (cube[RIGHT] & 0xF0000000) >> 8;
		cube[RIGHT] = (cube[RIGHT] & 0x0FFFFF00) | (up & 0x0000FF00) >> 8 | (up & 0x000000F0) << 24;

		cube[FRONT] = cube[FRONT] >> 8 | cube[FRONT] << 24;
		up = cube[UP];
		cube[UP] = (cube[UP] & 0xFFFF000F) | (cube[LEFT] & 0x00FFF000) >> 8;
		cube[LEFT] = (cube[LEFT] & 0xFF000FFF) | (cube[DOWN] & 0xFFF00000) >> 8;
		cube[DOWN] = (cube[DOWN] & 0x000FFFFF) | (cube[RIGHT] & 0x000000FF) << 24 | (cube[RIGHT] & 0xF0000000) >> 8;
		cube[RIGHT] = (cube[RIGHT] & 0x0FFFFF00) | (up & 0x0000FF00) >> 8 | (up & 0x000000F0) << 24;
	} break;
	case F3: {
		cube[FRONT] = cube[FRONT] >> 8 | cube[FRONT] << 24;
		uint32_t up = cube[UP];
		cube[UP] = (cube[UP] & 0xFFFF000F) | (cube[LEFT] & 0x00FFF000) >> 8;
		cube[LEFT] = (cube[LEFT] & 0xFF000FFF) | (cube[DOWN] & 0xFFF00000) >> 8;
		cube[DOWN] = (cube[DOWN] & 0x000FFFFF) | (cube[RIGHT] & 0x000000FF) << 24 | (cube[RIGHT] & 0xF0000000) >> 8;
		cube[RIGHT] = (cube[RIGHT] & 0x0FFFFF00) | (up & 0x0000FF00) >> 8 | (up & 0x000000F0) << 24;

		cube[FRONT] = cube[FRONT] >> 8 | cube[FRONT] << 24;
		up = cube[UP];
		cube[UP] = (cube[UP] & 0xFFFF000F) | (cube[LEFT] & 0x00FFF000) >> 8;
		cube[LEFT] = (cube[LEFT] & 0xFF000FFF) | (cube[DOWN] & 0xFFF00000) >> 8;
		cube[DOWN] = (cube[DOWN] & 0x000FFFFF) | (cube[RIGHT] & 0x000000FF) << 24 | (cube[RIGHT] & 0xF0000000) >> 8;
		cube[RIGHT] = (cube[RIGHT] & 0x0FFFFF00) | (up & 0x0000FF00) >> 8 | (up & 0x000000F0) << 24;

		cube[FRONT] = cube[FRONT] >> 8 | cube[FRONT] << 24;
		up = cube[UP];
		cube[UP] = (cube[UP] & 0xFFFF000F) | (cube[LEFT] & 0x00FFF000) >> 8;
		cube[LEFT] = (cube[LEFT] & 0xFF000FFF) | (cube[DOWN] & 0xFFF00000) >> 8;
		cube[DOWN] = (cube[DOWN] & 0x000FFFFF) | (cube[RIGHT] & 0x000000FF) << 24 | (cube[RIGHT] & 0xF0000000) >> 8;
		cube[RIGHT] = (cube[RIGHT] & 0x0FFFFF00) | (up & 0x0000FF00) >> 8 | (up & 0x000000F0) << 24;
	} break;
	case B: {
		cube[BACK] = cube[BACK] >> 8 | cube[BACK] << 24;
		uint32_t up = cube[UP];
		cube[UP] = (cube[UP] & 0x000FFFFF) | (cube[RIGHT] & 0x00FFF000) << 8;
		cube[RIGHT] = (cube[RIGHT] & 0xFF000FFF) | (cube[DOWN] & 0x0000FFF0) << 8;
		cube[DOWN] = (cube[DOWN] & 0xFFFF000F) | (cube[LEFT] & 0x000000FF) << 8 | (cube[LEFT] & 0xF0000000) >> 24;
		cube[LEFT] = (cube[LEFT] & 0x0FFFFF00) | (up & 0xFF000000) >> 24 | (up & 0x00F00000) << 8;
	} break;
	case B2: {
		cube[BACK] = cube[BACK] >> 8 | cube[BACK] << 24;
		uint32_t up = cube[UP];
		cube[UP] = (cube[UP] & 0x000FFFFF) | (cube[RIGHT] & 0x00FFF000) << 8;
		cube[RIGHT] = (cube[RIGHT] & 0xFF000FFF) | (cube[DOWN] & 0x0000FFF0) << 8;
		cube[DOWN] = (cube[DOWN] & 0xFFFF000F) | (cube[LEFT] & 0x000000FF) << 8 | (cube[LEFT] & 0xF0000000) >> 24;
		cube[LEFT] = (cube[LEFT] & 0x0FFFFF00) | (up & 0xFF000000) >> 24 | (up & 0x00F00000) << 8;

		cube[BACK] = cube[BACK] >> 8 | cube[BACK] << 24;
		up = cube[UP];
		cube[UP] = (cube[UP] & 0x000FFFFF) | (cube[RIGHT] & 0x00FFF000) << 8;
		cube[RIGHT] = (cube[RIGHT] & 0xFF000FFF) | (cube[DOWN] & 0x0000FFF0) << 8;
		cube[DOWN] = (cube[DOWN] & 0xFFFF000F) | (cube[LEFT] & 0x000000FF) << 8 | (cube[LEFT] & 0xF0000000) >> 24;
		cube[LEFT] = (cube[LEFT] & 0x0FFFFF00) | (up & 0xFF000000) >> 24 | (up & 0x00F00000) << 8;
	} break;
	case B3: {
		cube[BACK] = cube[BACK] >> 8 | cube[BACK] << 24;
		uint32_t up = cube[UP];
		cube[UP] = (cube[UP] & 0x000FFFFF) | (cube[RIGHT] & 0x00FFF000) << 8;
		cube[RIGHT] = (cube[RIGHT] & 0xFF000FFF) | (cube[DOWN] & 0x0000FFF0) << 8;
		cube[DOWN] = (cube[DOWN] & 0xFFFF000F) | (cube[LEFT] & 0x000000FF) << 8 | (cube[LEFT] & 0xF0000000) >> 24;
		cube[LEFT] = (cube[LEFT] & 0x0FFFFF00) | (up & 0xFF000000) >> 24 | (up & 0x00F00000) << 8;

		cube[BACK] = cube[BACK] >> 8 | cube[BACK] << 24;
		up = cube[UP];
		cube[UP] = (cube[UP] & 0x000FFFFF) | (cube[RIGHT] & 0x00FFF000) << 8;
		cube[RIGHT] = (cube[RIGHT] & 0xFF000FFF) | (cube[DOWN] & 0x0000FFF0) << 8;
		cube[DOWN] = (cube[DOWN] & 0xFFFF000F) | (cube[LEFT] & 0x000000FF) << 8 | (cube[LEFT] & 0xF0000000) >> 24;
		cube[LEFT] = (cube[LEFT] & 0x0FFFFF00) | (up & 0xFF000000) >> 24 | (up & 0x00F00000) << 8;

		cube[BACK] = cube[BACK] >> 8 | cube[BACK] << 24;
		up = cube[UP];
		cube[UP] = (cube[UP] & 0x000FFFFF) | (cube[RIGHT] & 0x00FFF000) << 8;
		cube[RIGHT] = (cube[RIGHT] & 0xFF000FFF) | (cube[DOWN] & 0x0000FFF0) << 8;
		cube[DOWN] = (cube[DOWN] & 0xFFFF000F) | (cube[LEFT] & 0x000000FF) << 8 | (cube[LEFT] & 0xF0000000) >> 24;
		cube[LEFT] = (cube[LEFT] & 0x0FFFFF00) | (up & 0xFF000000) >> 24 | (up & 0x00F00000) << 8;
	} break;
	}
	return cube;
}

Face getSticker(Cube& cube, Face face, int stickerIndex) {
	return (Face)(cube[face] >> ((7 - stickerIndex) * 4) & 0xF);
}

int cornerTwistIndex(Cube& cube) {
	int index = 0;

	// ULF
	index += (getSticker(cube, FRONT, 0) == UP || getSticker(cube, FRONT, 0) == DOWN);
	index += 2 * (getSticker(cube, LEFT, 2) == UP || getSticker(cube, LEFT, 2) == DOWN);

	// ULB
	index += 3 * (getSticker(cube, LEFT, 0) == UP || getSticker(cube, LEFT, 0) == DOWN);
	index += 3 * 2 * (getSticker(cube, BACK, 2) == UP || getSticker(cube, BACK, 2) == DOWN);

	// URF
	index += 9 * (getSticker(cube, RIGHT, 0) == UP || getSticker(cube, RIGHT, 0) == DOWN);
	index += 9 * 2 * (getSticker(cube, FRONT, 2) == UP || getSticker(cube, FRONT, 2) == DOWN);

	// URB
	index += 27 * (getSticker(cube, BACK, 0) == UP || getSticker(cube, BACK, 0) == DOWN);
	index += 27 * 2 * (getSticker(cube, RIGHT, 2) == UP || getSticker(cube, RIGHT, 2) == DOWN);

	// DLF
	index += 81 * (getSticker(cube, LEFT, 4) == UP || getSticker(cube, LEFT, 4) == DOWN);
	index += 81 * 2 * (getSticker(cube, FRONT, 6) == UP || getSticker(cube, FRONT, 6) == DOWN);

	// DLB
	index += 243 * (getSticker(cube, BACK, 4) == UP || getSticker(cube, BACK, 4) == DOWN);
	index += 243 * 2 * (getSticker(cube, LEFT, 6) == UP || getSticker(cube, LEFT, 6) == DOWN);

	// DRF
	index += 729 * (getSticker(cube, FRONT, 4) == UP || getSticker(cube, FRONT, 4) == DOWN);
	index += 729 * 2 * (getSticker(cube, RIGHT, 6) == UP || getSticker(cube, RIGHT, 6) == DOWN);

	return index;
}
std::array<int, 6> cmap = { 0,4,0,2,0,1 };
std::array<int, 8> factorial = { 0,1,2,6,24,120,720,5040 };
int cornerLocationIndex(Cube& cube) {
	std::array<int, 8> pos;

	// ULF
	pos[0] = (cmap[getSticker(cube, UP, 6)] | cmap[getSticker(cube, LEFT, 2)] | cmap[getSticker(cube, FRONT, 0)]);

	// ULB
	pos[1] = (cmap[getSticker(cube, UP, 0)] | cmap[getSticker(cube, LEFT, 0)] | cmap[getSticker(cube, BACK, 2)]);

	// URF
	pos[2] = (cmap[getSticker(cube, UP, 4)] | cmap[getSticker(cube, RIGHT, 0)] | cmap[getSticker(cube, FRONT, 2)]);

	// URB
	pos[3] = (cmap[getSticker(cube, UP, 2)] | cmap[getSticker(cube, RIGHT, 2)] | cmap[getSticker(cube, BACK, 0)]);

	// DLF
	pos[4] = (cmap[getSticker(cube, DOWN, 0)] | cmap[getSticker(cube, LEFT, 4)] | cmap[getSticker(cube, FRONT, 6)]);

	// DLB
	pos[5] = (cmap[getSticker(cube, DOWN, 6)] | cmap[getSticker(cube, LEFT, 6)] | cmap[getSticker(cube, BACK, 4)]);

	// DRF
	pos[6] = (cmap[getSticker(cube, DOWN, 2)] | cmap[getSticker(cube, RIGHT, 6)] | cmap[getSticker(cube, FRONT, 4)]);

	// DRB
	pos[7] = (cmap[getSticker(cube, DOWN, 4)] | cmap[getSticker(cube, RIGHT, 4)] | cmap[getSticker(cube, BACK, 6)]);

	int index = 0;
	int count;
	for (int i = 0; i < 7; i++) {
		count = 0;
		for (int j = i + 1; j < 8; j++) {
			count += pos[j] < pos[i];
		}
		index += count * factorial[7 - i];
	}
	return index;
}

std::array<std::array<int, 4>, 8> FB_edges = { {
	{FRONT, 1, UP, 5},
	{FRONT, 3, RIGHT, 7},
	{FRONT, 5, DOWN, 1},
	{FRONT, 7, LEFT, 3},
	{BACK, 1, UP, 1},
	{BACK, 3, LEFT, 7},
	{BACK, 5, DOWN, 5},
	{BACK, 7, RIGHT, 3}
} };
std::array<std::array<int, 4>, 4> S_edges = { {
	{UP, 3, RIGHT, 1},
	{UP, 7, LEFT, 1},
	{DOWN, 3, RIGHT, 5},
	{DOWN, 7, LEFT, 5},
} };
bool stage0Complete(Cube& cube) {
	// FB edges
	for (int i = 0; i < 8; i++) {
		Face fb_sticker = getSticker(cube, (Face)FB_edges[i][0], FB_edges[i][1]);
		Face other_sticker = getSticker(cube, (Face)FB_edges[i][2], FB_edges[i][3]);
		if (other_sticker == FRONT || other_sticker == BACK) {
			return false;
		} else if (fb_sticker != FRONT && fb_sticker != BACK && (other_sticker == UP || other_sticker == DOWN)) {
			return false;
		}
	}

	// S edges
	for (int i = 0; i < 4; i++) {
		Face ud_sticker = getSticker(cube, (Face)S_edges[i][0], S_edges[i][1]);
		Face other_sticker = getSticker(cube, (Face)S_edges[i][2], S_edges[i][3]);
		if (other_sticker == FRONT || other_sticker == BACK) {
			return false;
		} else if (ud_sticker != FRONT && ud_sticker != BACK && (other_sticker == UP || other_sticker == DOWN)) {
			return false;
		}
	}
	
	return true;
}
bool stage1Complete(Cube& cube) {
	for (int i = 0; i < 8; i+=1) {
		Face R_sticker = getSticker(cube, RIGHT, i);
		Face L_sticker = getSticker(cube, LEFT, i);
		if ((R_sticker != RIGHT && R_sticker != LEFT) || (L_sticker != RIGHT && L_sticker != LEFT)) {
			return false;
		}
	}

	return true;
}
bool stage2Complete(Cube& cube) {
	for (int i = 0; i < 8; i+=1) {
		for (int j = 0; j < 3; j++) {
			Face A_sticker = getSticker(cube, (Face)(j*2+1), i);
			Face B_sticker = getSticker(cube, (Face)(j*2), i);
			if ((A_sticker != j * 2 && A_sticker != j * 2 + 1) || (B_sticker != j * 2 && B_sticker != j * 2 + 1)) {
				return false;
			}
		}
	}
	return true;
}
bool stage3Complete(Cube& cube) {
	return cube[UP] == 0x00000000 && cube[DOWN] == 0x11111111 && cube[LEFT] == 0x22222222 && cube[RIGHT] == 0x33333333 && cube[FRONT] == 0x44444444 && cube[BACK] == 0x55555555;
}

int stage0heuristic(Cube& cube) {
	return 0;
}
int stage1heuristic(Cube& cube) {
	int total = 0;
	for (int i = 0; i < 8; i+=2) {
		total += getSticker(cube, UP, i) == RIGHT || getSticker(cube, UP, i) == LEFT;
		total += getSticker(cube, DOWN, i) == RIGHT || getSticker(cube, DOWN, i) == LEFT;
		total += (getSticker(cube, FRONT, i) == RIGHT || getSticker(cube, FRONT, i) == LEFT) * 2;
		total += (getSticker(cube, BACK, i) == RIGHT || getSticker(cube, BACK, i) == LEFT) * 2;
	}

	bool total_ea = false;
	total_ea = total_ea || getSticker(cube, UP, 1) == RIGHT || getSticker(cube, UP, 1) == LEFT;
	total_ea = total_ea || getSticker(cube, DOWN, 5) == RIGHT || getSticker(cube, DOWN, 5) == LEFT;
	bool total_eb = false;
	total_eb = total_eb || getSticker(cube, UP, 5) == RIGHT || getSticker(cube, UP, 5) == LEFT;
	total_eb = total_eb || getSticker(cube, DOWN, 1) == RIGHT || getSticker(cube, DOWN, 1) == LEFT;
	return std::max((total+3) / 4, total_ea + total_eb);
}
int* stage2database;
int stage2heuristic(Cube& cube) {
	int val = stage2database[cornerTwistIndex(cube) + cornerLocationIndex(cube) * 2187];
	if (val < 0 || val > 7) {
		std::cout << cornerTwistIndex(cube) + cornerLocationIndex(cube) * 2187 << " ERROR - cube read from database is not in stage 1" << std::endl;
		return -1;
	}
	return val;
}
int stage3heuristic(Cube& cube) {
	int v = 0;
	for (int i = 0; i < 8; i += 2) {
		v += getSticker(cube, UP, i) == DOWN;
	}

	int e = 0;
	for (int i = 1; i < 8; i += 2) {
		e += getSticker(cube, UP, i) == DOWN;
	}
	e += getSticker(cube, FRONT, 1) == BACK;
	e += getSticker(cube, FRONT, 5) == BACK;

	return std::max((v + 1) / 2, e);
}

bool dfs(Cube cube, int depth, std::vector<Move>& allowedMoves, Move previous, std::function<bool(Cube&)> predicate, std::function<int(Cube&)> heuristic, std::vector<Move>& moves) {
	if (depth == 0) {
		return predicate(cube);
	}
	int h = heuristic(cube);
	if (h == -1) {
		std::cin >> h;
	}
	if (depth - h < 0) {
		return false;
	}
	for (Move i : allowedMoves) {
		if (previous == NOTHING || (i%6 != previous%6 && !(i%2==0 && previous%6==(i%6)+1))) {
			moves.push_back(i);
			if (dfs(executeMove(cube, i), depth - 1, allowedMoves, i, predicate, heuristic, moves)) {
				return true;
			}
			moves.pop_back();
		}
	}
	return false;
}
bool dfs_thread(Cube cube, int depth, std::vector<Move>& allowedMoves, Move previous, std::function<bool(Cube&)> predicate, std::function<int(Cube&)> heuristic, std::array<Move,64>& moves, int moveLoc) {
	if (depth == 0) {
		return predicate(cube);
	}
	if (depth - heuristic(cube) < 0) {
		return false;
	}
	for (Move i : allowedMoves) {
		if (previous == NOTHING || (i % 6 != previous % 6 && !(i % 2 == 0 && previous % 6 == (i % 6) + 1))) {
			moves[moveLoc] = i;
			if (dfs_thread(executeMove(cube, i), depth - 1, allowedMoves, i, predicate, heuristic, moves, moveLoc + 1)) {
				return true;
			}
		}
	}
	return false;
}
bool dfs_thread_init(Cube cube, int depth, std::vector<Move>& allowedMoves, Move previous, std::function<bool(Cube&)> predicate, std::function<int(Cube&)> heuristic, std::vector<Move>& moves) {
	std::array<Move,64> moveList;
	if (dfs_thread(cube, depth, allowedMoves, previous, predicate, heuristic, moveList, 0)) {
		moves.push_back(previous);
		for (int i=0; i < depth; i++) {
			moves.push_back(moveList[i]);
		}
		return true;
	}
	return false;
}

bool iterativeDeepening(Cube& cube, int depth, std::vector<Move>& allowedMoves, std::function<bool(Cube&)> predicate, std::function<int(Cube&)> heuristic, std::vector<Move>& moves) {
	for (int i = 0; i <= depth; i++) {
		std::cout << "Depth: " << i << std::endl;
		if (dfs(cube, i, allowedMoves, NOTHING, predicate, heuristic, moves)) {
			return true;
		}
	}
	return false;
}
bool iterativeDeepening_threads(Cube& cube, int depth, std::vector<Move>& allowedMoves, std::function<bool(Cube&)> predicate, std::function<int(Cube&)> heuristic, std::vector<Move>& moves) {
	for (int i = 0; i <= depth; i++) {
		std::cout << "Depth: " << i << std::endl;
		if (i > 7) {
			std::vector<std::thread> threads;
			std::vector<std::vector<Move>> thread_moves;
			std::vector<std::vector<Move>> allowed_moves_list;
			for (Move m:allowedMoves) {
				allowed_moves_list.push_back(allowedMoves);
				thread_moves.push_back(moves);
			}
			for (int j = 0; j < allowedMoves.size();j++) {
				threads.push_back(std::thread(dfs_thread_init, executeMove(cube, (Move)allowedMoves[j]), i - 1, std::ref(allowed_moves_list.at(j)), (Move)allowedMoves[j], predicate, heuristic, std::ref(thread_moves.at(j))));
			}

			for (auto& th : threads) {
				th.join();
			}

			for (std::vector<Move> moveList : thread_moves) {
				if (moveList.size() > moves.size()) {
					moves = moveList;
					return true;
				}
			}
		}
		else {
			if (dfs(cube, i, allowedMoves, NOTHING, predicate, heuristic, moves)) {
				return true;
			}
		}
	}
	return false;
}

std::vector<Move> solve(Cube cube) {
	std::vector<Move> solution;

	std::vector<Move> allowedMoves = { L2, R2, F2, B2, U2, D2, L, R, F, B, U, D, L3, R3, F3, B3, U3, D3 };
	bool found = iterativeDeepening_threads(cube, 6, allowedMoves, stage0Complete, stage0heuristic, solution);
	std::cout << "stage 0 complete" << std::endl;


	Cube newCube = cube;
	for (Move move : solution) {
		newCube = executeMove(newCube, move);
	}
	allowedMoves = { L2, R2, F2, B2, U2, D2, L, R, F, B, L3, R3, F3, B3 };
	found = iterativeDeepening_threads(newCube, 10, allowedMoves, stage1Complete, stage1heuristic, solution);
	std::cout << "stage 1 complete" << std::endl;


	stage2database = new int[88179840];
	std::ifstream inFile("stage2database.bin", std::ios::binary);
	if (!inFile) {
		std::cerr << "ERROR - could not find stage2database.bin" << std::endl;
	}
	inFile.read(reinterpret_cast<char*>(stage2database), 88179840 * sizeof(int));

	newCube = cube;
	for (Move move : solution) {
		newCube = executeMove(newCube, move);
	}
	allowedMoves = { L2, R2, F2, B2, U2, D2, L, R, L3, R3 };
	found = iterativeDeepening_threads(newCube, 13, allowedMoves, stage2Complete, stage2heuristic, solution);
	std::cout << "stage 2 complete" << std::endl;

	delete[] stage2database;


	newCube = cube;
	for (Move move : solution) {
		newCube = executeMove(newCube, move);
	}
	allowedMoves = { L2, R2, F2, B2, U2, D2 };
	found = iterativeDeepening_threads(newCube, 15, allowedMoves, stage3Complete, stage3heuristic, solution);
	std::cout << "stage 3 complete" << std::endl;

	return solution;
}