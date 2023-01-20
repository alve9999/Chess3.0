#include "Ai.h"
Move* best_move;
#include <chrono>
#include <thread>
int MinMax(int depth,bool colour,bool first,int alpha,int beta, sf::RenderWindow& window, sf::RectangleShape White_square, sf::RectangleShape Black_square) {
	if (depth == 0) {
		return evaluate(colour);
	}
	else {
		std::vector<Move> local_moves;
		GenerateMoves(colour, local_moves);
		int maximum = -100000;
		for (int i = 0; i < local_moves.size(); i++) {
			Move made_move = make_move(local_moves[i], colour);
			/*std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			chess_pattern(window, White_square, Black_square);
			draw_board(window);
			window.display();*/
			int eval = -MinMax(depth - 1, !colour, false,-beta,-alpha, window, White_square, Black_square);
			unmake_move(made_move, colour);
			if (maximum<eval) {
				maximum = eval;
				if (first and i==0) {
					best_move = new Move(local_moves[i]);
				}
				else if (first) {
					best_move = new Move(local_moves[i]);
				}
			}
			alpha = std::max(alpha,maximum);
			if (beta <= alpha) {
				break;
			}
		}
		return maximum;
	}
}

Move* ai(int depth,bool colour, sf::RenderWindow& window, sf::RectangleShape White_square, sf::RectangleShape Black_square) {
	MinMax(depth, colour, true,-100000,100000, window, White_square, Black_square);
	return best_move;
}