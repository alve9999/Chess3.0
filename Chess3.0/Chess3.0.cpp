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
    load_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	srand(0);
	gen_random(random_key);

    Magic_initialisation();
    gennTable();
    Ginit();
    run_game();
}

