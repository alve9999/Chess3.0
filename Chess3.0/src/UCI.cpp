#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h> 
#include "Ai.h"
#include "Moves.h"
#include "Bit.h"
#include "UCI.h"
#include "Board.h"
#include "Graphics.h"
#include <fstream>
#include "../book.h"

bool first = true;
void proccess_command(std::string str,bool colour){
    std::cout<<"command:"<<str<<std::endl;
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    
    while(std::getline(ss, token, ' ')) {
        tokens.push_back(token);
    }
    if (tokens[0] == "quit") {
        exit(1);
    }
    if(tokens[0] == "position"){
        if(tokens.back()!="startpos"){
	        Move *move = algebraic_to_move(tokens.back());
	        make_move(*move,!colour);
	        delete move;
        }
    }
    if (tokens[0] == "isready") {
        std::cout << "readyok\n";
    } 
    else if (tokens[0] == "uci") {
        std::cout << "id name chess_engien\nid author Alve Lindell\nuciok\n";
    } 
    else if (tokens[0] == "go") {
        if(first){
            read_book();
            first = false;
        }
        Move move = *ai(2000, colour);
	    make_move(move,colour);
	    int from = move.from;
	    int to = move.to;
        std::string promotion = (move.special == 0b10) ? "q" : "";
        std::cout <<"bestmove "<< to_algebraic(RANK(from),FILE(from)) << to_algebraic(RANK(to),FILE(to)) << promotion << std::endl;
    }
}

void uci_run_game(bool colour){
    while(1){
        if (std::cin.peek() != EOF) {
	        std::string str;
	        std::getline(std::cin, str);
	        proccess_command(str,colour);
        }
    }
}
