#include "cube.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <string>

bool dfs_stage2(Cube cube, int depth, std::vector<Move>& allowedMoves, Move previous) {
	if (depth == 0) {
		bool found = true;
		for (int i = 0; i < 8; i += 2) {
			for (int j = 0; j < 3; j++) {
				Face A_sticker = getSticker(cube, (Face)(j * 2 + 1), i);
				Face B_sticker = getSticker(cube, (Face)(j * 2), i);
				if ((A_sticker != j * 2 && A_sticker != j * 2 + 1) || (B_sticker != j * 2 && B_sticker != j * 2 + 1)) {
					found = false;
				}
			}
		}
		return found;
	}
	for (Move i : allowedMoves) {
		if (previous == NOTHING || (i % 6 != previous % 6 && !(i % 2 == 0 && previous % 6 == (i % 6) + 1))) {
			if (dfs_stage2(executeMove(cube, i), depth - 1, allowedMoves, i)) {
				return true;
			}
		}
	}
	return false;
}
int iterativeDeepening_stage2(Cube& cube, int depth) {
	std::vector<Move> allowedMoves = { L2, R2, F2, B2, U2, D2, L, R, L3, R3 };
	for (int i = 0; i <= depth; i++) {
		if (dfs_stage2(cube, i, allowedMoves, NOTHING)) {
			return i;
		}
	}
	std::cout << "ERROR - no solution found" << std::endl;
	return -1;
}

bool stage1Complete_new(Cube& cube) {
	for (int i = 0; i < 7; i += 2) {
		Face R_sticker = getSticker(cube, RIGHT, i);
		Face L_sticker = getSticker(cube, LEFT, i);
		if ((R_sticker != RIGHT && R_sticker != LEFT) || (L_sticker != RIGHT && L_sticker != LEFT)) {
			return false;
		}
	}

	return true;
}

int generate() {
	int* data = new int[88179840];
	int cperm = 0;
	std::array<int, 8> perm = { 0,1,2,3,4,5,6,7 };
	Cube cube;
	int c0; int c1; int c2; int c3; int c4; int c5; int c6; int c7;
	int i = -1;
	do {
		for (int c = 0; c < 2187; c++) {
			i++;
			if ((i % 250000) == 0) {
				std::cout << i << " / 88,179,840" << std::endl;
			}
			cube = { 0x00000000,0x01010101,0x02020202,0x03030303,0x04040404,0x05050505};
			c0 = c % 3; c1 = c / 3 % 3; c2 = c / 9 % 3; c3 = c / 27 % 3; c4 = c / 81 % 3; c5 = c / 243 % 3; c6 = c / 729 % 3; c7 = (3 - ((c0 + c1 + c2 + c3 + c4 + c5 + c6) % 3)) % 3;
			cube[UP] |= (cubies[perm[0]][c0] << 4) | (cubies[perm[1]][c1] << 28) | (cubies[perm[2]][c2] << 12) | (cubies[perm[3]][c3] << 20);
			cube[DOWN] |= (cubies[perm[4]][c4] << 28) | (cubies[perm[5]][c5] << 4) | (cubies[perm[6]][c6] << 20) | (cubies[perm[7]][c7] << 12);
			cube[LEFT] |= cubies[perm[0]][(c0 + 1) % 3] << 20 | cubies[perm[1]][(c1 + 2) % 3] << 28 | cubies[perm[4]][(c4 + 2) % 3] << 12 | cubies[perm[5]][(c5 + 1) % 3] << 4;
			cube[RIGHT] |= cubies[perm[2]][(c2 + 2) % 3] << 28 | cubies[perm[3]][(c3 + 1) % 3] << 20 | cubies[perm[6]][(c6 + 1) % 3] << 4 | cubies[perm[7]][(c7 + 2) % 3] << 12;
			cube[FRONT] |= cubies[perm[0]][(c0 + 2) % 3] << 28 | cubies[perm[2]][(c2 + 1) % 3] << 20 | cubies[perm[4]][(c4 + 1) % 3] << 4 | cubies[perm[6]][(c6 + 2) % 3] << 12;
			cube[BACK] |= cubies[perm[1]][(c1 + 1) % 3] << 20 | cubies[perm[3]][(c3 + 2) % 3] << 28 | cubies[perm[5]][(c5 + 2) % 3] << 12 | cubies[perm[7]][(c7 + 1) % 3] << 4;
			if (!stage1Complete_new(cube)) {
				continue;
			}
			data[cperm * 2187 + c] = iterativeDeepening_stage2(cube, 10);
		}
		cperm++;
	} while (std::next_permutation(perm.begin(), perm.end()));

	std::ofstream outFile("stage2database.bin", std::ios::out | std::ios::binary);
	
	outFile.write(reinterpret_cast<const char*>(data), 88179840 * sizeof(int));
	outFile.close();

	delete[] data;
	return 0;
}