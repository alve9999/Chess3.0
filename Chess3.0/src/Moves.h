#pragma once
#include <cstdint>
#include <iostream>
#include <vector>
#include "Graphics.h"
#include "Board.h"
#include "Moves.h"
#include "Bit.h"
#include "Magic.h"

__declspec(selectany) uint64_t nTable[64] = {};
__declspec(selectany) uint64_t kTable[64] = {};

void gennTable();

struct Move{
	uint8_t from;
	uint8_t to;
	uint8_t fromtype;
	//int that stores wether the move is special
	//1=capture,10=promotion,100=Qcastel,1000=Kcastel,10000=en passant
	uint8_t special;
	uint8_t totype;
	Move(uint8_t aFrom, uint8_t aTo, uint8_t aSpecial, uint8_t aFromtype);
};

inline void wPmoves(int coordinate, std::vector<Move*>& Moves);

inline void bPmoves(int coordinate, std::vector<Move*>& Moves);

void TableMoves(uint64_t a,int colour, std::vector<Move*>& Moves,int position,int type);

void GenerateMoves(int colour, std::vector<Move*>& Moves);

Move make_move(Move& move, bool colour);

void unmake_move(Move& move, bool colour);
