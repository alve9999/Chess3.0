#pragma once
#include <cstdint>
//Static class that represents the main playing board
#include <string>
#include <stack>

constexpr int p = 0;
constexpr int n = 1;
constexpr int b = 2;
constexpr int r = 3;
constexpr int q = 4;
constexpr int k = 5;

constexpr int W = 0;
constexpr int B = 1;

void print_bitboard(uint64_t bitboard);

struct Board {

	//bitboard containing whether there is a piece on a given square using the y*8+x bit
	uint64_t Occupancy = 0;

	//bitboards containing the type on each squares and the colour of the piece on the square colours
	//pawns,knights,bishops,rooks,queens,kings
	uint64_t Types[6] = {0,0,0,0,0,0};
	// white = 0 black = 1
	uint64_t colours[2] = { 0,0 };
	//variable that holds the colour of the current player
	int Currentcolour = 1;
	int mgphase = 0;
	int egphase = 0;
	std::stack<uint8_t> enpassant;
};


void load_fen(std::string fen);

extern Board board;