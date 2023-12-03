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

int alg_to_coord(const std::string& square)
{
    int column = square[0] - 'a';
    int row = 8 - (square[1] - '0');
    return (8 * row + column);
}



Move* algebraic_to_move(std::string alg){
    int from = alg_to_coord(alg.substr(0,2));
    int to = alg_to_coord(alg.substr(2,4));
    int special = 0;
    int type = 0;
    if(ISSET(board.Types[p],from)){
        type = p;
    }
    if(ISSET(board.Types[b],from)){
        type = b;
    }
    if(ISSET(board.Types[n],from)){
        type = n;
    }
    if(ISSET(board.Types[r],from)){
        type = r;
    }
    if(ISSET(board.Types[q],from)){
        type = q;
    }
    if(ISSET(board.Types[k],from)){
        type = k;
    }
    if(abs(to-from)==16 and (type == p)){
        special |= 1;
    }
    if((RANK(to)==0 or RANK(to)==7) and (type == p)){
        special |= 2;
    }
    if (ISSET(board.Occupancy, to)) {
        special |= 16;
    }
    if((abs(to-from)==7 or abs(to-from)==9) and (type == p) and (NOTSET(board.Occupancy,to))){
        special |= 32;
    }
    if(type == k){
        if(from==4){
	        if(to==6){
	            special |= 4;
	        }
	        if(to==2){
	            special |= 8;
	        }
        }
        if(from == 60){
	        if(to==62){
	            special |= 4;
	        }
	        if(to == 58){
	            special |= 8;
	        }
        }
    }
    return new Move(from,to,special,type);
}

std::string to_algebraic(int row, int col) {
    return std::string(1, 'a' + col) + std::to_string(8 - row);
}
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
