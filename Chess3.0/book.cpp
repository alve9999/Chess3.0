#include "book.h"
#include <string>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <unordered_map>

std::unordered_map<std::string, std::string>* the_book;

int getRandomNumber(int maxNumber) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(0, maxNumber);

    return distribution(gen);
}

void read_book() {
    std::string file_path = "opening_book.txt";
    std::ifstream input_file(file_path);


    std::stringstream book_stream;
    book_stream << input_file.rdbuf();
    input_file.close();

    the_book = new std::unordered_map<std::string, std::string>;

    std::string current_pos;
    std::vector<std::pair<std::string, int>> moves;

    while (1){
        std::string next_line;
        std::getline(book_stream, next_line);
        if (next_line=="end"){
            break;
        }
        if (next_line.substr(0,3)=="pos") {
	        if (!current_pos.empty()){
                int sum = 0;
                for (const auto& pair : moves) {
                    sum += pair.second;
                }
                for (const auto& pair : moves) {
                    int i = getRandomNumber(sum);
                    i -= pair.second;
                    if(i<=0){
                        the_book->insert({ current_pos,pair.first });
                        break;
                    }
                }
                moves.clear();
	        }
            current_pos=next_line.substr(4, next_line.size());
            std::istringstream iss(current_pos);
            std::string temp;
            iss >> current_pos;
            iss >> temp;
            current_pos += " " + temp;
        }
        else {
            std::string move = next_line.substr(0, 5);
            int occurences = std::stoi(next_line.substr(5, next_line.size()));
            moves.emplace_back(std::pair<std::string, int>(move,occurences));
        }

    }
}