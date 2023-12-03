#include "Moves.h"
#include "Bit.h"
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <functional>
#ifdef __linux__
#define _BitScanForward64(var,num) (*var = __builtin_ffsll(num)-1)

#else
#include <intrin.h>
#pragma intrinsic(_BitScanForward64)
#endif

uint64_t nTable[64] = {};
uint64_t kTable[64] = {};


void gennTable() {
	const int directions[2][8] = { {6,10,-6,-10,17,15,-17,-15 }, { 1,-1, -7, -8, -9, 7, 8, 9 }};
	const int tiles[2][8] = { {1,1,-1,-1,2,2,-2,-2},{ 0,0,-1,-1,-1,1,1,1 } };
	for (int k = 0; k < 2; k++) {
		for (int j = 0; j < 64; j++) {
			uint64_t possibleMoves = 0;
			for (int i = 0; i < 8; i++) {
				if (-1 < j - directions[k][i] && j - directions[k][i] < 64) {
					if ((j / 8) - tiles[k][i] == (j - directions[k][i]) / 8) {
						possibleMoves ^= 1ULL << (j - directions[k][i]);
					}
				}
			}
			k ? kTable[j] = possibleMoves: nTable[j] = possibleMoves;
		}
	}
}

#define NUM_DIRECTIONS 8	
#define DIR_X {0, -1,  1,  0, 1, -1, 1, -1}
#define DIR_Y {-1,  0,  0,  1, 1, 1,-1, -1}

Move::Move(uint8_t aFrom, uint8_t aTo, uint8_t aSpecial, uint8_t aFromtype){
	from = aFrom;
	to = aTo;
	special = aSpecial;
	fromtype = aFromtype;
	totype = 8;
}

bool Move::operator==(const Move& other) const {
	return other.from == from && other.to == to;
}


std::ostream& operator<<(std::ostream& os, const Move& obj)
{
	os << "From:" << (int)obj.from%8 +1 <<"," << (int)obj.from / 8 +1 << std::endl << "FromType:" << (int)obj.fromtype << std::endl << "To:" << (int)obj.to % 8 +1 << "," << (int)obj.to / 8 + 1 << std::endl;
	if (obj.totype!=8) {
		os << "ToType:" << (int)obj.totype << std::endl;
	}
	os << "Special:" << (int)obj.special << std::endl;
	return os;
}

uint64_t check_pin(bool colour, std::unordered_map<int, uint64_t>& map) {
	uint64_t pinned = 0;
	unsigned long king;
	_BitScanForward64(&king, board.colours[colour] & board.Types[k]);
	uint8_t x = FILE(king);
	uint8_t y = RANK(king);
	int dir_x[NUM_DIRECTIONS] = DIR_X;
	int dir_y[NUM_DIRECTIONS] = DIR_Y;
	for (int dir = 0; dir < NUM_DIRECTIONS; dir++) {
		uint8_t pos = 255;
		for (int i = 1; i < 8; ++i) {
			int cur_x = x + dir_x[dir] * i;
			int cur_y = y + dir_y[dir] * i;
			if (cur_x < 0 || cur_x >= 8 || cur_y < 0 || cur_y >= 8) {
				break;
			}
			if (ISSET(board.colours[colour], POS(cur_x, cur_y))) {
				if (pos == 255) {
					pos = POS(cur_x, cur_y);
				}
				else {
					break;
				}
			}
			if (ISSET(board.colours[!colour], POS(cur_x, cur_y)) && !(ISSET(board.Types[dir < 4 ? r : b], POS(cur_x, cur_y)) || ISSET(board.Types[q], POS(cur_x, cur_y)))) {
				break;	
			}
			if ((pos != 255) && ISSET(board.colours[!colour], POS(cur_x, cur_y)) && (ISSET(board.Types[dir < 4 ? r : b], POS(cur_x, cur_y)) || ISSET(board.Types[q], POS(cur_x, cur_y)))) {
				SET(pinned, pos);
				uint64_t mask = 0;
				for (int i = 1; i < 8; ++i) {
					int cur_x2 = x + dir_x[dir] * i;
					int cur_y2 = y + dir_y[dir] * i;
					if (cur_x2 < 0 || cur_x2 >= 8 || cur_y2 < 0 || cur_y2 >= 8) {
						break;
					}
					SET(mask, POS(cur_x2, cur_y2));
				}
				map[pos] = mask;
				break;
			}
		}
	}
	return pinned;
}
#include <stdio.h>
bool is_attacked(int pos, bool colour) {
	if (colour == W) {
		if (RANK(pos) != 0) {
			if (FILE(pos) != 7) {
				if (ISSET(board.colours[B], pos - 7) && ISSET(board.Types[p], pos - 7)) {
					return true;
				}
			}
			if (FILE(pos) != 0) {
				if (ISSET(board.colours[B], pos - 9) && ISSET(board.Types[p], pos - 9)) {
					return true;
				}
			}
		}
	}
	else {
		if (RANK(pos) != 7) {
			if (FILE(pos) != 0) {
				if (ISSET(board.colours[W], pos + 7) && ISSET(board.Types[p], pos + 7)) {
					return true;
				}
			}
			if (FILE(pos) != 7) {
				if (ISSET(board.colours[W], pos + 9) && ISSET(board.Types[p], pos + 9)) {
					return true;
				}
			}
		}
	}
	uint8_t* t = static_cast<uint8_t*>(static_cast<void*>(&nTable[pos]));
	for (uint8_t i = 0; i < 8; i++) {
		if (t[i]) {
			for (uint8_t j = 0; j < 8; j++) {
				if (ISSET(t[i], j) && ISSET(board.colours[!colour], i * 8 + j) && ISSET(board.Types[n], i * 8 + j)) {
					return true;
				}
			}
		}
	}
	t = static_cast<uint8_t*>(static_cast<void*>(&kTable[pos]));
	for (uint8_t i = 0; i < 8; i++) {
		if (t[i]) {
			for (uint8_t j = 0; j < 8; j++) {
				if (ISSET(t[i], j) && ISSET(board.colours[!colour], i * 8 + j) && ISSET(board.Types[k], i * 8 + j)) {
					return true;
				}
			}
		}
	}
	uint64_t table = getBmagic(pos, board.Occupancy);
	t = static_cast<uint8_t*>(static_cast<void*>(&table));
	for (uint8_t i = 0; i < 8; i++) {
		if (t[i]) {
			for (uint8_t j = 0; j < 8; j++) {
				if (ISSET(t[i], j) && ISSET(board.colours[!colour], i * 8 + j) && (ISSET(board.Types[b], i * 8 + j) || ISSET(board.Types[q], i * 8 + j))) {
					return true;
				}
			}
		}
	}
	table = getRmagic(pos, board.Occupancy);
	t = static_cast<uint8_t*>(static_cast<void*>(&table));
	for (uint8_t i = 0; i < 8; i++) {
		if (t[i]) {
			for (uint8_t j = 0; j < 8; j++) {
				if (ISSET(t[i], j) && ISSET(board.colours[!colour], i * 8 + j) && (ISSET(board.Types[r], i * 8 + j) || ISSET(board.Types[q], i * 8 + j))) {
					return true;
				}
			}
		}
	}
	return false;
}

bool fixes_check(Move move, bool colour) {
	make_move(move, colour);
	unsigned long king;
	_BitScanForward64(&king, board.colours[colour] & board.Types[k]);
	bool remove = false;
	if (is_attacked(king, colour)) {
		remove = true;
	}
	unmake_move(move, colour);
	return remove;
}

void TableMoves(uint64_t a,int colour, std::vector<Move>& Moves,int position,int type) {
	uint8_t *t = static_cast<uint8_t*>(static_cast<void*>(&a));
	for (uint8_t i = 0; i < 8; i++) {
		if (t[i]) {
			for (uint8_t j = 0; j < 8; j++) {
				if ((t[i]>>j&1) and (1&~((board.Occupancy>> (i * 8 + j))))) {
					Moves.vector::emplace_back(Move(position,i * 8 + j, 0 ,type));
				}
				else if ((t[i] >> j & 1) and ((board.colours[!colour] >> (i * 8 + j) & 1))) {
					Moves.vector::emplace_back(Move(position, i * 8 + j, 16,type));
				}
			}
		}
	}
}

void TableMoves(uint64_t a, int colour, std::vector<Move>& Moves, int position, int type,uint64_t mask) {
	uint8_t* t = static_cast<uint8_t*>(static_cast<void*>(&a));
	for (uint8_t i = 0; i < 8; i++) {
		if (t[i]) {
			for (uint8_t j = 0; j < 8; j++) {
				if ((t[i] >> j & 1) and (1 & ~((board.Occupancy >> (i * 8 + j))))) {
					if(ISSET(mask,8*i+j))
						Moves.vector::emplace_back(Move(position, i * 8 + j, 0, type));
				}
				else if ((t[i] >> j & 1) and ((board.colours[!colour] >> (i * 8 + j) & 1))) {
					if (ISSET(mask, 8*i +j))
						Moves.vector::emplace_back(Move(position, i * 8 + j, 16, type));
				}
			}
		}
	}
}



//White pawn move generator using bitwise operations on bit boards
void wPmoves(int position, std::vector<Move>& Moves) {
	if (NOTSET(board.Occupancy,position-8)) {
		if (NOTSET(board.Occupancy, position - 16) && RANK(position) == 6) {
			Moves.vector::emplace_back(Move(position, position - 16, 1, 0));
		}
		if (RANK(position-8) == 0) {
			Moves.vector::emplace_back(Move(position, position - 8, 2, 0));
		}
		else {
			Moves.vector::emplace_back(Move(position, position - 8, 0, 0));
		}
	}
	if ((RANK(position) - RANK(position - 9) == 1) && (ISSET(board.colours[B], position - 9))) {
		if (RANK(position -8) == 0) {
			Moves.vector::emplace_back(Move(position, position - 9, 18, 0));
		}
		else {
			Moves.vector::emplace_back(Move(position, position - 9, 16, 0));
		}
	}
	else if ((RANK(position) - RANK(position - 9) == 1) && ((position - 9) == board.enpassant.top())) {
		if (!fixes_check(Move(position, position - 9, 32, 0), W))
			Moves.vector::emplace_back(Move(position, position - 9, 32, 0));
	}
	if ((RANK(position) - RANK(position - 7) == 1) && (ISSET(board.colours[B],position-7))) {
		if (RANK(position - 8) == 0) {
			Moves.vector::emplace_back(Move(position, position - 7, 18, 0));
		}
		else {
			Moves.vector::emplace_back(Move(position, position - 7, 16, 0));
		}
	}
	else if ((RANK(position) - RANK(position - 7) == 1) && ((position - 7) == board.enpassant.top())) {
		if(!fixes_check(Move(position, position - 7, 32, 0),W))
			Moves.vector::emplace_back(Move(position, position - 7, 32, 0));
	}
}
//Black pawn move generator using bitwise operations on bit boards
void bPmoves(int position, std::vector<Move>& Moves) {
	if(NOTSET(board.Occupancy, position + 8)) {
		if (NOTSET(board.Occupancy, position + 16)&&(RANK(position)==1)) {
			Moves.vector::emplace_back(Move(position, position + 16, 1, 0));
		}
		if (RANK(position + 8) == 7) {
			Moves.vector::emplace_back(Move(position, position + 8, 2, 0));
		}
		else {
			Moves.vector::emplace_back(Move(position, position + 8, 0, 0));
		}
	}
	if ((RANK(position) - RANK(position + 9) == -1) && (ISSET(board.colours[W], position + 9))) {
		if (RANK(position + 8) == 7) {
			Moves.vector::emplace_back(Move(position, position + 9, 18, 0));
		}
		else {
			Moves.vector::emplace_back(Move(position, position + 9, 16, 0));
		}
	}
	else if ((RANK(position) - RANK(position + 9) == -1) && ((position + 9) == board.enpassant.top())) {
		if (!fixes_check(Move(position, position + 9, 32, 0), B))
			Moves.vector::emplace_back(Move(position, position + 9, 32, 0));
	}
	if ((RANK(position) - RANK(position + 7) == -1) && (ISSET(board.colours[W], position + 7))) {
		if (RANK(position + 8) == 7) {
			Moves.vector::emplace_back(Move(position, position + 7, 18, 0));
		}
		else {
			Moves.vector::emplace_back(Move(position, position + 7, 16, 0));
		}
	}
	else if ((RANK(position) - RANK(position + 7) == -1) && ((position + 7) == board.enpassant.top())) {
		if (!fixes_check(Move(position, position +7, 32, 0), B))
			Moves.vector::emplace_back(Move(position, position + 7, 32, 0));
	}
}

void wPmoves(int position, std::vector<Move>& Moves, uint64_t mask) {
	if (NOTSET(board.Occupancy, position - 8)) {
		if (NOTSET(board.Occupancy, position - 16) && RANK(position) == 6) {
			if (ISSET(mask, position-16))
			Moves.vector::emplace_back(Move(position, position - 16, 1, 0));
		}
		if (RANK(position - 8) == 0) {
			if (ISSET(mask, position-8))
			Moves.vector::emplace_back(Move(position, position - 8, 2, 0));
		}
		else {
			if (ISSET(mask, position-8))
			Moves.vector::emplace_back(Move(position, position - 8, 0, 0));
		}
	}
	if ((RANK(position) - RANK(position - 9) == 1) && (ISSET(board.colours[B], position - 9))) {
		if (RANK(position - 8) == 0) {
			if (ISSET(mask, position-9))
			Moves.vector::emplace_back(Move(position, position - 9, 18, 0));
		}
		else {
			if (ISSET(mask, position-9))
			Moves.vector::emplace_back(Move(position, position - 9, 16, 0));
		}
	}
	else if ((RANK(position) - RANK(position - 9) == 1) && ((position - 9) == board.enpassant.top())) {
		if (!fixes_check(Move(position, position - 9, 32, 0), W))
			Moves.vector::emplace_back(Move(position, position - 9, 32, 0));
	}
	if ((RANK(position) - RANK(position - 7) == 1) && (ISSET(board.colours[B], position - 7))) {
		if (RANK(position - 8) == 0) {
			if (ISSET(mask, position-7))
			Moves.vector::emplace_back(Move(position, position - 7, 18, 0));
		}
		else {
			if (ISSET(mask, position-7))
			Moves.vector::emplace_back(Move(position, position - 7, 16, 0));
		}
	}
	else if ((RANK(position) - RANK(position - 7) == 1) && ((position -7) == board.enpassant.top())) {
		if (!fixes_check(Move(position, position - 7, 32, 0), W))
			Moves.vector::emplace_back(Move(position, position - 7, 32, 0));
	}
}

void bPmoves(int position, std::vector<Move>& Moves,uint64_t mask) {
	if (NOTSET(board.Occupancy, position + 8)) {
		if (NOTSET(board.Occupancy, position + 16) && (RANK(position) == 1)) {
			if(ISSET(mask,position+16))
			Moves.vector::emplace_back(Move(position, position + 16, 1, 0));
		}
		if (RANK(position + 8) == 7) {
			if (ISSET(mask, position+8))
			Moves.vector::emplace_back(Move(position, position + 8, 2, 0));
		}
		else {
			if (ISSET(mask, position+8))
			Moves.vector::emplace_back(Move(position, position + 8, 0, 0));
		}
	}
	if ((RANK(position) - RANK(position + 9) == -1) && (ISSET(board.colours[W], position + 9))) {
		if (RANK(position + 8) == 7) {
			if (ISSET(mask, position+9))
			Moves.vector::emplace_back(Move(position, position + 9, 18, 0));
		}
		else {
			if (ISSET(mask, position+9))
			Moves.vector::emplace_back(Move(position, position + 9, 16, 0));
		}
	}
	else if ((RANK(position) - RANK(position + 9) == -1) && ((position + 9) == board.enpassant.top())) {
		if (!fixes_check(Move(position, position + 9, 32, 0), B))
			Moves.vector::emplace_back(Move(position, position + 9, 32, 0));
	}
	if ((RANK(position) - RANK(position + 7) == -1) && (ISSET(board.colours[W], position + 7))) {
		if (RANK(position + 8) == 7) {
			if (ISSET(mask, position+7))
			Moves.vector::emplace_back(Move(position, position + 7, 18, 0));
		}
		else {
			if (ISSET(mask, position+7))
			Moves.vector::emplace_back(Move(position, position + 7, 16, 0));
		}
	}
	else if ((RANK(position) - RANK(position + 7) == -1) && ((position + 7) == board.enpassant.top())) {
		if (!fixes_check(Move(position, position + 7, 32, 0), B))
			Moves.vector::emplace_back(Move(position, position + 7, 32, 0));
	}
}
void Castling(int colour, std::vector<Move>& Moves) {
	//black
	if (colour) {
		//short
		if ((!(board.Occupancy & (1ULL << 5))) && !is_attacked(5,colour) && (!(board.Occupancy & (1ULL << 6))) && !is_attacked(6, colour) && (board.Types[3] & (1ULL << 7)) && (board.Types[5] & (1ULL << 4))) {
			Moves.vector::emplace_back(Move(4, 6, 4, 5));
		}
		//long
		if ((!(board.Occupancy & (1ULL << 3))) && !is_attacked(3, colour) && (!(board.Occupancy & (1ULL << 2))) && !is_attacked(2, colour) && (!(board.Occupancy & (1ULL << 1))) && (board.Types[3] & (1ULL)) && (board.Types[5] & (1ULL << 4))) {
			Moves.vector::emplace_back(Move(4, 2, 8, 5));
		}
	}
	//white
	else {
		//short
		if ((!(board.Occupancy & (1ULL << 62))) && !is_attacked(62, colour) && (!(board.Occupancy & (1ULL << 61))) && !is_attacked(61, colour) && (board.Types[3] & (1ULL << 63)) && (board.Types[5] & (1ULL << 60))) {
			Moves.vector::emplace_back(Move(60, 62, 4, 5));
		}
		//long
		if ((!(board.Occupancy & (1ULL << 59))) && !is_attacked(59, colour) && (!(board.Occupancy & (1ULL << 58))) && !is_attacked(58, colour) && (!(board.Occupancy & (1ULL << 57))) && (board.Types[3] & (1ULL << 56)) && (board.Types[5] & (1ULL << 60))) {
			Moves.vector::emplace_back(Move(60, 58, 8, 5));
		}
	}
}



void KingTableMoves(uint64_t a, int colour, std::vector<Move>& Moves, int position) {
	uint8_t* t = static_cast<uint8_t*>(static_cast<void*>(&a));
	for (uint8_t i = 0; i < 8; i++) {
		if (t[i]) {
			for (uint8_t j = 0; j < 8; j++) {
				if (!is_attacked(i * 8 + j,colour)) {
					if ((t[i] >> j & 1) and (1 & ~((board.Occupancy >> (i * 8 + j))))) {

						Moves.vector::emplace_back(Move(position, i * 8 + j, 0, k));
					}
					else if ((t[i] >> j & 1) and ((board.colours[!colour] >> (i * 8 + j) & 1))) {
						Moves.vector::emplace_back(Move(position, i * 8 + j, 16, k));
					}
				}
			}
		}
	}
}


//Function that generates all current legal moves for the current player
void GenerateMoves(int colour, std::vector<Move>& Moves) {
	//By reserving 50 moves the need for rezising the vector is reduced due to the amount of moves rarley exceeding 50 thereby greatly improving performance
	Moves.reserve(50);
	std::unordered_map<int, uint64_t> map;
	uint64_t pinned = check_pin(colour,map);
	unsigned long king;
	_BitScanForward64(&king,board.colours[colour] & board.Types[k]);
	bool check = is_attacked(king, colour);
	//Calls move calculation for each picece of the choosen colour
	if (!check) {
		Castling(colour, Moves);
	}
	for(int i = 0; i < 64; i++) {
		if (ISSET(board.colours[colour], i)) {
			if (ISSET(pinned, i)) {
				if ((board.Types[p] >> i) & colour)
					bPmoves(i, Moves,map[i]);
				if ((board.Types[p] >> i) & (!colour))
					wPmoves(i, Moves, map[i]);
				if ((board.Types[b] >> i) & 1)
					TableMoves(getBmagic(i, board.Occupancy), colour, Moves, i, 2, map[i]);
				if ((board.Types[r] >> i) & 1)
					TableMoves(getRmagic(i, board.Occupancy), colour, Moves, i, 3, map[i]);
				if ((board.Types[n] >> i) & 1)
					TableMoves(nTable[i], colour, Moves, i, 1, map[i]);
				if ((board.Types[k] >> i) & 1)
					KingTableMoves(kTable[i], colour, Moves, i);
				if ((board.Types[q] >> i) & 1) {
					TableMoves(getBmagic(i, board.Occupancy), colour, Moves, i, 4, map[i]);
					TableMoves(getRmagic(i, board.Occupancy), colour, Moves, i, 4, map[i]);
				}
			}
			else {
				if ((board.Types[p] >> i) & colour)
					bPmoves(i, Moves);
				if ((board.Types[p] >> i) & (!colour))
					wPmoves(i, Moves);
				if ((board.Types[b] >> i) & 1)
					TableMoves(getBmagic(i, board.Occupancy), colour, Moves, i, 2);
				if ((board.Types[r] >> i) & 1)
					TableMoves(getRmagic(i, board.Occupancy), colour, Moves, i, 3);
				if ((board.Types[n] >> i) & 1)
					TableMoves(nTable[i], colour, Moves, i, 1);
				if ((board.Types[k] >> i) & 1)
					KingTableMoves(kTable[i], colour, Moves, i);
				if ((board.Types[q] >> i) & 1) {
					TableMoves(getBmagic(i, board.Occupancy), colour, Moves, i, 4);
					TableMoves(getRmagic(i, board.Occupancy), colour, Moves, i, 4);
				}
			}
		}
	}
	if (check) {
		auto remove = std::bind(fixes_check, std::placeholders::_1, colour);
		Moves.erase(std::remove_if(Moves.begin(), Moves.end(), remove), Moves.end());
	}
	std::sort(Moves.begin(), Moves.end(), [](Move a, Move b){return a.special > b.special;});
}



Move make_move(Move& move,bool colour,const bool UCI) {
	//std::cout << (int)move.from << " " << (int)move.to << " " << (int)move.fromtype << " " << (int)move.special << std::endl;
	//capture
        if ((move.special & 16ULL) | (UCI)) {
		//clears to square
		board.colours[!colour] &= ~(1ULL << move.to);
		board.Occupancy &= ~(1ULL << move.to);
		for (int i = 0; i < 6; i++) {
		  if(i==5){
		    std::cout<<move<<std::endl;
		  }
			if ((board.Types[i] >> move.to) & 1) {
				move.totype = i;
				board.Types[i] &= ~(1ULL << move.to);
				break;
			}
		}
	}
	//clears from square
	board.Occupancy &= ~(1ULL << move.from);
	board.Types[move.fromtype] &= ~(1ULL << move.from);
	board.colours[colour] &= ~(1ULL << move.from);
		
	//sets to square
	board.Occupancy |= 1ULL << move.to;
	board.Types[move.fromtype] |= 1ULL << move.to;
	board.colours[colour] |= 1ULL << move.to;

	//double pawn push
	if (move.special & 1ULL) {
		if (colour == W) {
			board.enpassant.push(move.to + 8);
		}
		else {
			board.enpassant.push(move.to - 8);
		}
	}
	else {
		board.enpassant.push(-1);
	}
	//enpassant
	if (move.special & 32ULL) {
		if (colour == W) {
			UNSET(board.Occupancy, move.to + 8);
			UNSET(board.colours[B], move.to + 8);
			UNSET(board.Types[p], move.to + 8);
		}
		else {
			UNSET(board.Occupancy, move.to - 8);
			UNSET(board.colours[W], move.to - 8);
			UNSET(board.Types[p], move.to - 8);
		}
	}
	//promote
	if (move.special & 2ULL) {
		//sets promoted to square
		board.Types[q] |= 1ULL << move.to;
		board.Types[p] &= ~(1ULL << move.to);
	}
	//short castle
	if (move.special & 4) {
		if (colour) {
			board.Occupancy &= ~(1ULL<<7);
			board.Types[3] &= ~(1ULL<<7);
			board.colours[colour] &= ~(1ULL<<7);

			board.Occupancy |= 1ULL << 5;
			board.Types[3] |= 1ULL << 5;
			board.colours[colour] |= 1ULL << 5;
		}
		else {
			board.Occupancy &= ~(1ULL << 63);
			board.Types[3] &= ~(1ULL << 63);
			board.colours[colour] &= ~(1ULL << 63);

			board.Occupancy |= 1ULL << 61;
			board.Types[3] |= 1ULL << 61;
			board.colours[colour] |= 1ULL << 61;
		}
	}
	//long castle
	if (move.special&8) {
		if (colour) {
			board.Occupancy &= ~(1ULL);
			board.Types[3] &= ~(1ULL);
			board.colours[colour] &= ~(1ULL);

			board.Occupancy |= 1ULL << 3;
			board.Types[3] |= 1ULL << 3;
			board.colours[colour] |= 1ULL << 3;
		}
		else {
			board.Occupancy &= ~(1ULL << 56);
			board.Types[3] &= ~(1ULL << 56);
			board.colours[colour] &= ~(1ULL << 56);

			board.Occupancy |= 1ULL << 59;
			board.Types[3] |= 1ULL << 59;
			board.colours[colour] |= 1ULL << 59;
		}
	}
	return move;
}

void unmake_move(Move& move, bool colour) {
	//clears to square
	board.Types[move.fromtype] &= ~(1ULL << move.to);
	board.colours[colour] &= ~(1ULL << move.to);
	board.Occupancy &= ~(1ULL << move.to);
	//sets from square
	board.Occupancy |= 1ULL << move.from;
	board.colours[colour] |= 1ULL << move.from;
	board.Types[move.fromtype] |= 1ULL << move.from;


	board.enpassant.pop();
	if (move.special & 32ULL) {
		if (colour == W) {
			SET(board.Occupancy, move.to + 8);
			SET(board.colours[B], move.to + 8);
			SET(board.Types[p], move.to + 8);
		}
		else {
			SET(board.Occupancy, move.to - 8);
			SET(board.colours[W], move.to - 8);
			SET(board.Types[p], move.to - 8);
		}
	}
	if (move.special & 2ULL) {
		//clears promoted to square
		board.Types[4] &= ~(1ULL << move.to);
	}
	if (move.special & 16ULL) {
		//sets to square
		board.Types[move.totype] |= 1ULL << move.to;
		board.colours[!colour] |= 1ULL << move.to;
		board.Occupancy |= 1ULL << move.to;
	}
	
	//short castle
	if (move.special&4) {
		if (colour) {
			board.Occupancy &= ~(1ULL << 5);
			board.Types[3] &= ~(1ULL << 5);
			board.colours[colour] &= ~(1ULL << 5);

			board.Occupancy |= 1ULL << 7;
			board.Types[3] |= 1ULL << 7;
			board.colours[colour] |= 1ULL << 7;
		}
		else {
			board.Occupancy &= ~(1ULL << 61);
			board.Types[3] &= ~(1ULL << 61);
			board.colours[colour] &= ~(1ULL << 61);

			board.Occupancy |= 1ULL << 63;
			board.Types[3] |= 1ULL << 63;
			board.colours[colour] |= 1ULL << 63;
		}
	}
	//long castle
	if (move.special&8) {
		if (colour) {
			board.Occupancy &= ~(1ULL) << 3;
			board.Types[3] &= ~(1ULL << 3);
			board.colours[colour] &= ~(1ULL << 3);

			board.Occupancy |= 1ULL;
			board.Types[3] |= 1ULL;
			board.colours[colour] |= 1ULL;
		}
		else {
			board.Occupancy &= ~(1ULL << 59);
			board.Types[3] &= ~(1ULL << 59);
			board.colours[colour] &= ~(1ULL << 59);

			board.Occupancy |= 1ULL << 56;
			board.Types[3] |= 1ULL << 56;
			board.colours[colour] |= 1ULL << 56;
		}
	}

}
std::ostream& operator<<(std::ostream& os, const Info& obj) {
	os << "Caps:" << obj.caps << " Nodes:" << obj.nodes;
	return os;
}

#include <chrono>
#include <thread>

Info perft(int depth, int colour) {
	Info in;
	in.caps = 0;
	in.nodes = 0;
	if (depth == 0) {
		in.nodes = 1;
		in.caps = 0;
		return in;
	}

	unsigned long long nodes = 0;
	std::vector<Move> moves;
	GenerateMoves(colour,moves);

	for (size_t i = 0; i < moves.size(); i++) {
	       
		make_move(moves[i],colour);
		Info ret;
		ret = perft(depth - 1,!colour);
		in.caps += ret.caps;
		in.nodes += ret.nodes;
		if ((moves[i].special & 16ULL) && (depth == 1)) {
			//std::cout << moves[i] << std::endl;
			//std::cout << colour << std::endl;
			in.caps += 1;
		}
		unmake_move(moves[i], colour);
	}

	return in;
}
