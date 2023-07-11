#pragma once
#include <cstdint>
#include <iostream>
#include <vector>
#include "Graphics.h"
#include "Board.h"
#include "Moves.h"
#include "Bit.h"
#include "Magic.h"

#ifdef __linux__
#define __declspec(x)
#endif

extern uint64_t nTable[64];
extern uint64_t kTable[64];

void gennTable();

struct Move{
	uint8_t from;
	uint8_t to;
	uint8_t fromtype;
	//int that stores wether the move is special
	//1=double_pawn_push,10=promotion,100=Scastel,1000=Lcastel,10000=capture,100000=enpassant
	uint8_t special;
	uint8_t totype;
	Move(uint8_t aFrom, uint8_t aTo, uint8_t aSpecial, uint8_t aFromtype);
	bool operator==(const Move& other) const;
	
};
std::ostream& operator<<(std::ostream& os, const Move& obj);

struct Info {
	int nodes;
	int caps;
};

bool is_attacked(int pos, bool colour);

void GenerateMoves(int colour, std::vector<Move>& Moves);

Move make_move(Move& move, bool colour);

void unmake_move(Move& move, bool colour);

std::ostream& operator<<(std::ostream& os, const Info& obj);

Info perft(int depth, int colour);

