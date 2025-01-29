#pragma once
#include <array>
#include <vector>
#include <string>

// Cube has 6 faces, each represented by 8x4 bits. 4 bits encode each square
typedef std::array<uint32_t, 6> Cube;
enum Face { UP, DOWN, LEFT, RIGHT, FRONT, BACK };
enum Move { L2, R2, F2, B2, U2, D2, L, R, F, B, U, D, L3, R3, F3, B3, U3, D3, NOTHING };

extern const Face cubies[8][3];
extern const std::string MoveStrings[];

Cube executeMove(Cube cube, Move move);
Face getSticker(Cube& cube, Face face, int stickerIndex);
std::vector<Move> solve(Cube cube);