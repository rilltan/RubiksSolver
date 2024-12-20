#pragma once
#include <array>

// Cube has 6 faces, each represented by 8x4 bits. 4 bits encode each square
typedef std::array<uint32_t, 6> Cube;
enum Face { UP, DOWN, LEFT, RIGHT, FRONT, BACK };
enum Move { U, U2, U3, D, D2, D3, L, L2, L3, R, R2, R3, F, F2, F3, B, B2, B3 };

void executeMove(Cube& cube, Move move);