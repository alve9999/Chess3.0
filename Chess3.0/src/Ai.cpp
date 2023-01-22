#include "Ai.h"
#include "Hash.h"
Move* best_move;
#define UNKNOWN 989
#include <chrono>
#include <thread>
int sc = 0;
int tc = 0;
int MinMax(int depth,bool colour,bool first,int alpha,int beta, uint64_t key) {
	tc++;
	int val = 0;
	int hashf = 1;
	if ((val = TT.probe_hash(depth, alpha, beta, key))!=UNKNOWN){
		sc++;
		return val;
	}
	if (depth == 0) {
		val = evaluate(colour);
		TT.store(depth,val,0,key);
		return evaluate(colour);
	}
	else {
		std::vector<Move> local_moves;
		GenerateMoves(colour, local_moves);
		for (int i = 0; i < local_moves.size(); i++) {
			Move made_move = make_move(local_moves[i], colour);
			uint64_t new_key = update_hash(key,local_moves[i],colour);
			val = -MinMax(depth - 1, !colour, false,-beta,-alpha,new_key);
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

Move* ai(int depth,bool colour) {
	MinMax(depth, colour, true,-100000,100000, create_hash(colour));
	std::cout <<"skiped:"<< sc<< "total:"<<tc<<std::endl;
	std::cout << "percentage:" << (double)sc / (double)tc<<std::endl;
	sc = 0;
	tc = 0;
	return best_move;
}