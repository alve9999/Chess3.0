#include <iostream>
#include <cstdint>
#include "src/Board.h"
#include "src/Moves.h"
#include "src/Magic.h"
#include "src/Bit.h"
#include "src/Ai.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "src/Evaluation.h"
#include "src/Hash.h"
#include "src/Graphics.h"
#include "src/UCI.h"


int main(){
    board.enpassant.push(-1);
    Magic_initialisation();
    gennTable();
    load_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    //Ginit();
    
    srand(0);
    //std::cout << perft(6, 1).nodes << std::endl;
    gen_random(random_key);
    //run_game();
    uci_run_game(1);
}

