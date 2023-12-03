#include <iostream>
#include <string>
#include "UCI.h"
#include "src/Board.h"
#include "src/Ai.h"

void send_UCI_response(const std::string& response) {
    std::cout << response << std::endl;
}

void handle_position(const std::string& position_command) {
    std::cout << position_command << "\n";
    std::string pos = position_command.substr(0, position_command.find(" "));
    if (pos == "startpos") {
        load_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    }
    else{
        load_fen(pos);
    }
}

void handle_go(const std::string& goCommand) {
    Move* best_move = ai(3000,1);
    send_UCI_response(best_move->to_algebraic());
}

void UCI() {
    std::string command;

    while (true) {
        std::getline(std::cin, command);

        if (command == "uci") {
            send_UCI_response("id name Chess3.0");
            send_UCI_response("id author Alve");
            send_UCI_response("uciok");
        }
        else if (command == "isready") {
            send_UCI_response("readyok");
        }
        else if (command.compare(0, 8, "position") == 0) {
            handle_position(command.substr(9,command.length()));
        }
        else if (command.compare(0, 2, "go") == 0) {
            handle_go(command);
        }
        else if (command == "quit") {
            break;
        }
    }
}