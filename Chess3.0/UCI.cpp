#include <iostream>
#include <string>
#include "UCI.h"
#include "src/Board.h"

void sendUCIResponse(const std::string& response) {
    std::cout << response << std::endl;
}

void handlePosition(const std::string& positionCommand) {
    std::cout << positionCommand << "\n";
    std::string pos = positionCommand.substr(0, positionCommand.find(" "));
    if (pos == "startpos") {
        load_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    }
    else{
        load_fen(pos);
    }
}

void handleGo(const std::string& goCommand) {

}

void UCI() {
    std::string command;

    while (true) {
        std::getline(std::cin, command);

        if (command == "uci") {
            sendUCIResponse("id name Chess3.0");
            sendUCIResponse("id author Alve");
            sendUCIResponse("uciok");
        }
        else if (command == "isready") {
            sendUCIResponse("readyok");
        }
        else if (command.compare(0, 8, "position") == 0) {
            handlePosition(command.substr(9,command.length()));
        }
        else if (command.compare(0, 2, "go") == 0) {
            handleGo(command);
        }
        else if (command == "quit") {
            break;
        }
    }
}