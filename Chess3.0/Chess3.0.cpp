#include <iostream>
#include <cstdint>
#include "src/Board.h"
#include "src/Moves.h"
#include "src/Magic.h"
#include "src/graphics.h"
#include "src/Bit.h"
#include "src/Ai.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "src/Evaluation.h"
#include "src/Hash.h"

using namespace std;

int main(){
    board.enpassant.push(-1);
    Magic_initialisation();
    gennTable();
    load_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    print_piece_info();
	srand(0);
	gen_random(random_key);


    Ginit();
    cout << perft(7, W) << endl;
    run_game();
}

