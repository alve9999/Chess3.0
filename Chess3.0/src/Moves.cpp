#include "Moves.h"


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

Move::Move(uint8_t aFrom, uint8_t aTo, uint8_t aSpecial, uint8_t aFromtype){
	from = aFrom;
	to = aTo;
	special = aSpecial;
	fromtype = aFromtype;
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
					Moves.vector::emplace_back(Move(position, i * 8 + j, 1,type));
				}
			}
		}
	}
}


//White pawn move generator using bitwise operations on bit boards
void wPmoves(int position, std::vector<Move>& Moves) {
	if (!((board.Occupancy >> (position - 8)) & 1)) {
		if ((!((board.Occupancy >> (position - 16)) & 1)) && (position / 8) == 6) {
			Moves.vector::emplace_back(Move(position, position - 16, 0, 0));
		}
		if (((position - 8) / 8) == 0) {
			Moves.vector::emplace_back(Move(position, position - 8, 2, 0));
		}
		else {
			Moves.vector::emplace_back(Move(position, position - 8, 0, 0));
		}
	}
	if (((position - 1) % 8 != 0) != 0 && (board.colours[1] >> (position - 9) & 1)) {
		if (((position - 8) / 8) == 0) {
			Moves.vector::emplace_back(Move(position, position - 9, 3, 0));
		}
		else {
			Moves.vector::emplace_back(Move(position, position - 9, 1, 0));
		}
	}
	if (((position + 1) % 8 != 0) && (board.colours[1] >> (position - 7) & 1)) {
		if (((position - 8) / 8) == 0) {
			Moves.vector::emplace_back(Move(position, position - 7, 3, 0));
		}
		else {
			Moves.vector::emplace_back(Move(position, position - 7, 1, 0));
		}
	}
}
//Black pawn move generator using bitwise operations on bit boards
void bPmoves(int position, std::vector<Move>& Moves) {
	if (!((board.Occupancy >> (position + 8)) & 1)) {
		if ((!((board.Occupancy >> (position + 16)) & 1)) && (position / 8) == 1) {
			Moves.vector::emplace_back(Move(position, position + 16, 0, 0));
		}
		if (((position + 8) / 8) == 7) {
			Moves.vector::emplace_back(Move(position, position + 8, 2, 0));
		}
		else {
			Moves.vector::emplace_back(Move(position, position + 8, 0, 0));
		}
	}
	if (((position + 1) % 8 != 0) && (board.colours[0] >> (position + 9) & 1)) {
		if (((position + 8) / 8) == 7) {
			Moves.vector::emplace_back(Move(position, position + 9, 3, 0));
		}
		else {
			Moves.vector::emplace_back(Move(position, position + 9, 1, 0));
		}
	}
	if (((position - 1) % 8 != 0) && (board.colours[0] >> (position + 7) & 1)) {
		if (((position + 8) / 8) == 7) {
			Moves.vector::emplace_back(Move(position, position + 7, 3, 0));
		}
		else {
			Moves.vector::emplace_back(Move(position, position + 7, 1, 0));
		}
	}
}
void Castling(int colour, std::vector<Move>& Moves) {
	//black
	if (colour) {
		//short
		if ((!(board.Occupancy & (1ULL << 5))) && (!(board.Occupancy & (1ULL << 6))) && (board.Types[3] & (1ULL << 7)) && (board.Types[5] & (1ULL << 4))) {
			Moves.vector::emplace_back(Move(4, 6, 4, 5));
		}
		//long
		if ((!(board.Occupancy & (1ULL << 3))) && (!(board.Occupancy & (1ULL << 2))) && (!(board.Occupancy & (1ULL << 1))) && (board.Types[3] & (1ULL)) && (board.Types[5] & (1ULL << 4))) {
			Moves.vector::emplace_back(Move(4, 2, 8, 5));
		}
	}
	//white
	else {
		//short
		if ((!(board.Occupancy & (1ULL << 62))) && (!(board.Occupancy & (1ULL << 61))) && (board.Types[3] & (1ULL << 63)) && (board.Types[5] & (1ULL << 60))) {
			Moves.vector::emplace_back(Move(60, 62, 4, 5));
		}
		//long
		if ((!(board.Occupancy & (1ULL << 59))) && (!(board.Occupancy & (1ULL << 58))) && (!(board.Occupancy & (1ULL << 57))) && (board.Types[3] & (1ULL << 56)) && (board.Types[5] & (1ULL << 60))) {
			Moves.vector::emplace_back(Move(60, 58, 8, 5));
		}
	}
}
//Function that generates all current legal moves for the current player
void GenerateMoves(int colour, std::vector<Move>& Moves) {
	//By reserving 50 moves the need for rezising the vector is reduced due to the amount of moves rarley exceeding 50 thereby greatly improving performance
	Moves.reserve(50);

	//Calls move calculation for each picece of the choosen colour
	Castling(colour, Moves);
	for (int i = 0; i < 64; i++) {
		if ((board.colours[colour] >> i)&1) {
			if ((board.Types[0] >> i) & colour)
				bPmoves(i, Moves);
			if ((board.Types[0] >> i) & (!colour))
				wPmoves(i, Moves);
			if ((board.Types[2] >> i) & 1)
				TableMoves(getBmagic(i,board.Occupancy), colour, Moves, i,2);
			if ((board.Types[3] >> i) & 1)
				TableMoves(getRmagic(i,board.Occupancy), colour, Moves, i,3);
			if ((board.Types[1] >> i) & 1)
				TableMoves(nTable[i], colour, Moves, i,1);
			if ((board.Types[5] >> i) & 1)
				TableMoves(kTable[i], colour, Moves, i,5);
			if ((board.Types[4] >> i) & 1) {
				TableMoves(getBmagic(i,board.Occupancy), colour, Moves, i,4);
				TableMoves(getRmagic(i,board.Occupancy), colour, Moves, i,4);
			}
		}
	}
}

Move make_move(Move& move,bool colour) {
	//std::cout << (int)move.from << " " << (int)move.to << " " << (int)move.fromtype << " " << (int)move.special << std::endl;
	//capture
	if (move.special & 1ULL) {
		//clears to square
		board.colours[!colour] &= ~(1ULL << move.to);
		board.Occupancy &= ~(1ULL << move.to);
		for (int i = 0; i < 6; i++) {
			if ((board.Types[i] >> move.to) & 1) {
				move.totype = i;
				board.Types[i] &= ~(1ULL << move.to);
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
	//promote
	if (move.special & 2ULL) {
		//sets promoted to square
		board.Types[4] |= 1ULL << move.to;
		board.Types[0] &= ~(1ULL << move.to);
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

	if (move.special & 2ULL) {
		//clears promoted to square
		board.Types[4] &= ~(1ULL << move.to);
	}
	if (move.special & 1ULL) {
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


