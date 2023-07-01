#include "Ai.h"
#include "Hash.h"
Move* best_move;
#define UNKNOWN 989

int sc = 0;
int tc = 0;
int MinMax(int depth,bool colour,bool first,float alpha,float beta, uint64_t key,float score) {
	if (board.won[!colour]) {
		return -INFINITY;
	}
	if (board.won[colour]) {
		return INFINITY;
	}
	tc++;
	float val = 0;
	int hashf = 1;
	if ((val = TT.probe_hash(depth, alpha, beta, key)) != UNKNOWN) {
		sc++;
		return val;
	}
	if (depth == 0) {
		val = score;
		TT.store(depth, val, 0, key);
		return val;
	}

	else {
		std::vector<Move> local_moves;
		GenerateMoves(colour, local_moves);
		for (int i = 0; i < local_moves.size(); i++) {
			Move made_move = make_move(local_moves[i], colour);
			uint64_t new_key = update_hash(key,local_moves[i],colour);
			int new_score = update_eval(colour, score, local_moves[i]);
			val = -MinMax(depth - 1, !colour, false,-beta,-alpha,new_key,-new_score);
			unmake_move(made_move, colour);
			if (beta <= val) {
				TT.store(depth, val, 2, key);
				return beta;
			}
			if (val > alpha) {
				hashf = 0;
				alpha = val;
				if (first) {
					best_move = new Move(local_moves[i]);
				}
			}
		}
		TT.store(depth, val, hashf, key);
		return alpha;
	}
}
//piece phase value
const int gamephaseInc[5] = { 0,1,1,2,4 };

Move* ai(int depth,bool colour) {
	int phase = 0;
	phase += popCount64bit(board.Types[1]) * gamephaseInc[1];
	phase += popCount64bit(board.Types[2]) * gamephaseInc[2];
	phase += popCount64bit(board.Types[3]) * gamephaseInc[3];
	phase += popCount64bit(board.Types[4]) * gamephaseInc[4];
	board.mgphase = phase;
	board.egphase = 24 - phase;
	float score = evaluate(colour);
	MinMax(depth, colour, true,-100000,100000, create_hash(colour),score);
	std::cout <<"skiped:"<< sc<< "total:"<<tc<<std::endl;
	std::cout << "percentage:" << (double)sc / (double)tc<<std::endl;
	sc = 0;
	tc = 0;
	return best_move;
}