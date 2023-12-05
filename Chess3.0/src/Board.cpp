#include "Board.h"
#include <cstdint>
#include <string>
#include <vector>
#include <iostream>
#include "Bit.h"
Board board;

void print_bitboard(uint64_t bitboard) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((bitboard >> (i * 8 + j)) & 1)
            {
                std::cout << "1 ";
            }
            else
            {
                std::cout << "0 ";
            }
        }
        std::cout << std::endl;
    }
}

void load_fen(std::string fen) {
    size_t pos_start = 0;
    size_t pos_end;
    std::string token;
    std::vector<std::string> pieces;
    std::vector<std::string> info;

    while ((pos_end = fen.find("/", pos_start)) != std::string::npos) {
        token = fen.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + 1;
        pieces.push_back(token);

    }

    std::string rest = fen.substr(pos_start);
    pos_start = 0;
    pos_end = rest.find(" ", pos_start);
    pieces.push_back(rest.substr(pos_start, pos_end - pos_start));
    pos_start = pos_end + 1;

    while ((pos_end = rest.find(" ", pos_start)) != std::string::npos) {
        token = rest.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + 1;
        info.push_back(token);

    }

    info.push_back(rest.substr(pos_start));


    int pos = 0;
    for (std::string i : pieces) {
        for (char j : i){
            if (isdigit(j)) {
                pos += j - '0';
            }
            else {
                SET(board.Occupancy, pos);
                if (isupper(j)) {
                    SET(board.colours[W], pos);
                    j = tolower(j);
                }
                else {
                    SET(board.colours[B],pos);
                }
                switch (j) {
                case 'p':
                    SET(board.Types[p],pos);
                    break;
                case 'n':
                    SET(board.Types[n], pos);
                    break;
                case 'b':
                    SET(board.Types[b], pos);
                    break;
                case 'r':
                    SET(board.Types[r], pos);
                    break;
                case 'q':
                    SET(board.Types[q], pos);
                    break;
                case 'k':
                    SET(board.Types[k], pos);
                    break;
                }
                pos++;
            }
        }

    }

}

std::string create_fen(){
    std::string row,fen;
    int empty_count=0;
	for(int i = 0; i<64;i++){
        if (i % 8 == 0 and i!=0) {
            if(empty_count!=0){
                row += std::to_string(empty_count);
                empty_count = 0;
            }
            fen += row + "/";
            row = "";
        }
        if(ISSET(board.Occupancy,i)){
	        if (empty_count!=0){
                row += std::to_string(empty_count);
                empty_count = 0;
	        }
            for (int j = 0; j < 6; j++) {
                if (ISSET(board.Types[j], i)) {
                    if (ISSET(board.colours[1], i)) {
                        row += int_to_string[j + 6];
                    }
                    else {
                        row += int_to_string[j];
                    }
                }
            }
        }
        else{
            empty_count++;
        }
        if (i == 63) {
            if (empty_count != 0) {
                row += std::to_string(empty_count);
                empty_count = 0;
            }
            fen += row;
            row = "";
        }
	}
    fen += " " + int_to_colour[board.Currentcolour];
    return fen;
}