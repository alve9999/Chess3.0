#include "Ai.h"
#include "Hash.h"
#include "Graphics.h"
#include <chrono>
#include <thread>
#include <cmath>
#include <atomic>
Move* best_move;
#define UNKNOWN 989


std::atomic<bool> timeIsUp(false);

int global_depth;

int sc = 0;
int tc = 0;
int MinMax(int depth,bool colour,float alpha,float beta, uint64_t key,float score) {
    if(timeIsUp){
		return 0;
    }
	tc++;
	float val = 0;
	int hashf = 1;
	if (((val = TT.probe_hash(depth, alpha, beta, key)) != UNKNOWN) && global_depth!=1) {
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
	    if (local_moves.size() == 0) {
			unsigned long king;
			_BitScanForward64(&king, board.colours[colour] & board.Types[k]);
			if (is_attacked(king, colour)) {
				return INFINITY;
			}
			else {
				return 0;
			}
		}
		if (global_depth == depth && global_depth != 1) {
			local_moves.erase(std::find(local_moves.begin(), local_moves.end(), *best_move));
			local_moves.insert(local_moves.begin(), *best_move);
		}
		for (int i = 0; i < local_moves.size(); i++) {
			make_move(local_moves[i], colour);
			uint64_t new_key = update_hash(key,local_moves[i],colour);
			int new_score = update_eval(colour, score, local_moves[i]);
			val = -MinMax(depth - 1, !colour,-beta,-alpha,new_key,-new_score);
			unmake_move(local_moves[i], colour);
			if (timeIsUp) {
				return 0;
			}
			if (beta <= val) {
				TT.store(depth, val, 2, key);
				return beta;
			}
			if (val > alpha) {
				hashf = 0;
				alpha = val;
				if (global_depth==depth) {
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

void iterative_deepening(bool colour){
	float score = evaluate(colour);
	best_move = NULL;

	global_depth = 1;
	while(!timeIsUp){
		MinMax(global_depth, colour, -100000, 100000, create_hash(colour), score);
		printf("finished depth %d\n",global_depth);
		global_depth++;
	}
}

void timer(std::chrono::milliseconds duration) {
    std::this_thread::sleep_for(duration);
    timeIsUp = true;
}

Move* ai(int time,bool colour) {
	int phase = 0;
	phase += popCount64bit(board.Types[1]) * gamephaseInc[1];
	phase += popCount64bit(board.Types[2]) * gamephaseInc[2];
	phase += popCount64bit(board.Types[3]) * gamephaseInc[3];
	phase += popCount64bit(board.Types[4]) * gamephaseInc[4];
	board.mgphase = phase;
	board.egphase = 24 - phase;

	std::thread searchThread(iterative_deepening, colour);
	
	std::chrono::milliseconds duration(time);
	std::thread timerThread(timer, duration); 

	searchThread.join();
	timerThread.join();
	timeIsUp = false;
	std::cout <<"skiped:"<< sc<< "total:"<<tc<<std::endl;
	std::cout << "percentage:" << (double)sc / (double)tc<<std::endl;
	sc = 0;
	tc = 0;
	return best_move;
}
