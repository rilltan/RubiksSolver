#include "cube.h"

void executeMove(Cube &cube, Move move) {
	switch (move) {
	case U: {
		cube[UP] = cube[UP] << 8 | cube[UP] >> 24;
		uint32_t front = cube[FRONT];
		cube[FRONT] = (cube[FRONT] & 0x000FFFFF) | (cube[RIGHT] & 0xFFF00000);
		cube[RIGHT] = (cube[RIGHT] & 0x000FFFFF) | (cube[BACK] & 0xFFF00000);
		cube[BACK] = (cube[BACK] & 0x000FFFFF) | (cube[LEFT] & 0xFFF00000);
		cube[LEFT] = (cube[LEFT] & 0x000FFFFF) | (front & 0xFFF00000);
	} break;
	case U2: {
		executeMove(cube, U);
		executeMove(cube, U);
	} break;
	case U3: {
		executeMove(cube, U);
		executeMove(cube, U);
		executeMove(cube, U);
	} break;
	case D: {
		cube[DOWN] = cube[DOWN] << 8 | cube[DOWN] >> 24;
		uint32_t front = cube[FRONT];
		cube[FRONT] = (cube[FRONT] & 0xFFFF000F) | (cube[LEFT] & 0x0000FFF0);
		cube[LEFT] = (cube[LEFT] & 0xFFFF000F) | (cube[BACK] & 0x0000FFF0);
		cube[BACK] = (cube[BACK] & 0xFFFF000F) | (cube[RIGHT] & 0x0000FFF0);
		cube[RIGHT] = (cube[RIGHT] & 0xFFFF000F) | (front & 0x0000FFF0);
	} break;
	case D2: {
		executeMove(cube, D);
		executeMove(cube, D);
	} break;
	case D3: {
		executeMove(cube, D);
		executeMove(cube, D);
		executeMove(cube, D);
	} break;
	case L: {
		cube[LEFT] = cube[LEFT] << 8 | cube[LEFT] >> 24;
		uint32_t front = cube[FRONT];
		cube[FRONT] = (cube[FRONT] & 0x0FFFFF00) | (cube[UP] & 0xF00000FF);
		cube[UP] = (cube[UP] & 0x0FFFFF00) | (cube[BACK] & 0x00FF0000) >> 16 | (cube[BACK] & 0x0000F000) << 16;
		cube[BACK] = (cube[BACK] & 0xFF000FFF) | (cube[DOWN] & 0xF0000000) >> 16 | (cube[DOWN] & 0x000000FF) << 16;
		cube[DOWN] = (cube[DOWN] & 0x0FFFFF00) | (front & 0xF00000FF);
	} break;
	case L2: {
		executeMove(cube, L);
		executeMove(cube, L);
	} break;
	case L3: {
		executeMove(cube, L);
		executeMove(cube, L);
		executeMove(cube, L);
	} break;
	case R: {
		cube[RIGHT] = cube[RIGHT] << 8 | cube[RIGHT] >> 24;
		uint32_t front = cube[FRONT];
		cube[FRONT] = (cube[FRONT] & 0xFF000FFF) | (cube[DOWN] & 0x00FFF000);
		cube[DOWN] = (cube[DOWN] & 0xFF000FFF) | (cube[BACK] & 0x000000FF) << 16 | (cube[BACK] & 0xF0000000) >> 16;
		cube[BACK] = (cube[BACK] & 0x0FFFFF00) | (cube[UP] & 0x00FF0000) >> 16 | (cube[UP] & 0x0000F000) << 16;
		cube[UP] = (cube[UP] & 0xFF000FFF) | (front & 0x00FFF000);
	} break;
	case R2: {
		executeMove(cube, R);
		executeMove(cube, R);
	} break;
	case R3: {
		executeMove(cube, R);
		executeMove(cube, R);
		executeMove(cube, R);
	} break;
	case F: {
		cube[FRONT] = cube[FRONT] << 8 | cube[FRONT] >> 24;
		uint32_t up = cube[UP];
		cube[UP] = (cube[UP] & 0xFFFF000F) | (cube[LEFT] & 0x00FFF000) >> 8;
		cube[LEFT] = (cube[LEFT] & 0xFF000FFF) | (cube[DOWN] & 0xFFF00000) >> 8;
		cube[DOWN] = (cube[DOWN] & 0x000FFFFF) | (cube[RIGHT] & 0x000000FF) << 24 | (cube[RIGHT] & 0xF0000000) >> 8;
		cube[RIGHT] = (cube[RIGHT] & 0x0FFFFF00) | (up & 0x0000FF00) >> 8 | (up & 0x000000F0) << 24;
	} break;
	case F2: {
		executeMove(cube, F);
		executeMove(cube, F);
	} break;
	case F3: {
		executeMove(cube, F);
		executeMove(cube, F);
		executeMove(cube, F);
	} break;
	case B: {
		cube[BACK] = cube[BACK] << 8 | cube[BACK] >> 24;
		uint32_t up = cube[UP];
		cube[UP] = (cube[UP] & 0x000FFFFF) | (cube[RIGHT] & 0x00FFF000) << 8;
		cube[RIGHT] = (cube[RIGHT] & 0xFF000FFF) | (cube[DOWN] & 0x0000FFF0) << 8;
		cube[DOWN] = (cube[DOWN] & 0xFFFF000F) | (cube[LEFT] & 0x000000FF) << 8 | (cube[LEFT] & 0xF0000000) >> 24;
		cube[LEFT] = (cube[LEFT] & 0x0FFFFF00) | (up & 0xFF000000) >> 24 | (up & 0x00F00000) << 8;
	} break;
	case B2: {
		executeMove(cube, B);
		executeMove(cube, B);
	} break;
	case B3: {
		executeMove(cube, B);
		executeMove(cube, B);
		executeMove(cube, B);
	} break;
	}
}