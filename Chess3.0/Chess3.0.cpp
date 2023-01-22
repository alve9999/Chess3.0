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

int main(){
	//hash setup
	srand(0);
	gen_random(random_key);
	//initialisation
    sf::RenderWindow window(sf::VideoMode(150 * 8, 150 * 8), "Chess3.0");
    sf::RectangleShape Black_square(sf::Vector2f(150, 150));
    Black_square.setFillColor(sf::Color(106, 155, 65));
    sf::RectangleShape White_square(sf::Vector2f(150, 150));
    White_square.setFillColor(sf::Color(243, 243, 244));
    Magic_initialisation();
    gennTable();
    Ginit();
    chess_pattern(window, White_square, Black_square);
    draw_board(window);
    window.display();
	std::vector<Move> Moves;


	//your turn loop
	bool colour = 1;
	bool your_colour = 0;
	while (1) {
		int movedpiece;
		if (colour) {
			colour = 0;
		}
		else {
			colour = 1;
		}
		sf::Vector2i position;
		

		GenerateMoves(colour, Moves);
		chess_pattern(window, White_square, Black_square);
		draw_board(window);
		window.display();
		if (your_colour==colour and 0) {
			bool yourturn = 1;
			while (yourturn) {
				bool clicked = 0;
				//collect all events and check for left mouse button pressed
				sf::Event event;
				sf::Vector2i* position = new sf::Vector2i(200, 0);
				while (window.pollEvent(event)) {
					if (event.type == sf::Event::MouseButtonPressed) {
						if (event.mouseButton.button == sf::Mouse::Left) {
							position = new sf::Vector2i(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
							//check if pressed square is occupied by your colour
							if ((board.colours[colour] >> (position->x / 150 + 8 * ((position->y) / 150))) & 1) {
								clicked = 1;
								for (int i = 0; i < 6; i++) {
									if (board.Types[i] >> (position->x / 150 + 8 * (position->y / 150)) & 1) {
										movedpiece = i + colour * 6;
										board.Types[i] &= ~(1ULL << (position->x / 150 + 8 * ((position->y) / 150)));
									}
								}
								board.Occupancy ^= 1ULL << (position->x / 150 + 8 * ((position->y) / 150));
								board.colours[colour] ^= 1ULL << (position->x / 150 + 8 * ((position->y) / 150));
								sf::Vector2i to = move_piece(window, White_square, Black_square, movedpiece, colour);
								for (int i = 0; i < Moves.size(); i++) {
									if ((to.x / 150 + 8 * (to.y / 150)) == Moves[i].to && (position->x / 150 + 8 * (position->y / 150)) == Moves[i].from) {
										yourturn = false;
										make_move(Moves[i], colour);
										for (int j = Moves.size() - 1; j > -1; j--) {
											Moves.pop_back();
										}
										break;
									}
								}
							}
						}
					}
				}
				if (yourturn and clicked) {
					board.Types[movedpiece - 6 * colour] ^= (1ULL << (position->x / 150 + 8 * (position->y / 150)));
					board.Occupancy ^= 1ULL << (position->x / 150 + 8 * ((position->y) / 150));
					board.colours[colour] ^= 1ULL << (position->x / 150 + 8 * ((position->y) / 150));
					chess_pattern(window, White_square, Black_square);
					draw_board(window);
					window.display();
				}
				delete position;
			}
		}
		else {
			sf::Event events;
			window.pollEvent(events);
			//system("CLS");
			make_move(*ai(7,colour),colour);
			//std::cout <<"o:" << popCount64bit(board.Occupancy) << std::endl;
			//std::cout <<"p:" << popCount64bit(board.Types[0]) << std::endl;
			//std::cout <<"n:" << popCount64bit(board.Types[1]) << std::endl;
			//std::cout <<"b:" << popCount64bit(board.Types[2]) << std::endl;
			//std::cout <<"r:" << popCount64bit(board.Types[3]) << std::endl;
			//std::cout <<"q:" << popCount64bit(board.Types[4]) << std::endl;
			//std::cout <<"k:" << popCount64bit(board.Types[5]) << std::endl;
			//std::cout <<"w:" << popCount64bit(board.colours[0]) << std::endl;
			//std::cout <<"b:" << popCount64bit(board.colours[1]) << std::endl;
		}
	}
}

