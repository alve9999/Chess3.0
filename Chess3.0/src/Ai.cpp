#include "Ai.h"
Move* best_move;
#include <chrono>
#include <thread>
float MinMax(int depth,bool colour,bool first,float alpha,float beta) {
	if (depth == 0) {
		return evaluate(colour);
	}
	else {
		std::vector<Move*> local_moves;
		GenerateMoves(colour, local_moves);
		float maximum = -INFINITY;
		for (int i = 0; i < local_moves.size(); i++) {
			Move made_move = make_move(*local_moves[i], colour);
			float eval = -MinMax(depth - 1, !colour, false,-beta,-alpha);
			unmake_move(made_move, colour);
			if (maximum<eval) {
				maximum = eval;
				if (first and i==0) {
					best_move = new Move(*local_moves[i]);
				}
				else if (first) {
					delete best_move;
					best_move = new Move(*local_moves[i]);
				}
			}
			alpha = std::max(alpha,maximum);
			if (beta <= alpha) {
				break;
			}
		}
		for (int i = 0; i < local_moves.size(); i++) {
			Move* p = local_moves[i];
			delete p;
		}
		return maximum;
	}
}

Move* ai(int depth,bool colour) {
	MinMax(depth, colour, true,-INFINITY,INFINITY);
	return best_move;
}