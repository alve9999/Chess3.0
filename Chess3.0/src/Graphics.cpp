#include"Graphics.h"
#include <SFML/Graphics.hpp>
#include<vector>
#include"Board.h"
#include "Bit.h"
#include <iostream>
#include "Moves.h"
#include "Ai.h"
#include <chrono>
#include <thread>

sf::RectangleShape Black_square(sf::Vector2f(150, 150));

sf::RectangleShape White_square(sf::Vector2f(150, 150));

//hard code path becaus lazy
std::string dir = "C:/Users/alvel/Desktop/Dev/C++/Chess/Chess3.0/";

sf::RenderWindow window;

std::vector<sf::Sprite> sprites;
std::string sprite_names[] = { "bp.png", "bn.png", "bb.png", "br.png", "bq.png", "bk.png", "wp.png", "wn.png", "wb.png", "wr.png", "wq.png", "wk.png" };
sf::Texture ssprites[12];

sf::Clock deltaClock;

bool colour = 1;
bool your_colour =1;
int movedpiece;
sf::Vector2i position;

std::vector<Move> Moves;

void Ginit() {
    window.create(sf::VideoMode(150 * 8, 150 * 8), "Chess3.0");
	Black_square.setFillColor(sf::Color(106, 155, 65));
	White_square.setFillColor(sf::Color(243, 243, 244));
	for (int i = 0; i < 12; i++) {
		ssprites[i].loadFromFile(sprite_names[i], sf::IntRect(0, 0, 150, 150));
	}
	for (int i = 0; i < 12; i++) {
		sprites.vector::emplace_back(sf::Sprite());
		sprites[i].setTexture(ssprites[i]);
	}
}

void draw(sf::RenderWindow& window, int aposition, int colour, int type) {
	int y = floor(aposition / 8);
	int x = aposition - y * 8;
	sf::Sprite* sprite;
	if (colour == 0) { sprite = &sprites[type + 6]; }
	else { sprite = &sprites[type]; }
	sprite->setPosition(x * 150, y * 150);
	window.draw(*sprite);
}

void draw2(sf::RenderWindow& window,  int x, int y, int colour, int type){
	sf::Sprite* sprite;
	if (colour == 0) { sprite = &sprites[type + 6]; }
	else { sprite = &sprites[type]; }
	sprite->setPosition(x - 0.5 * 150, y - 0.5 * 150);
	window.draw(*sprite);
}

void draw_board(sf::RenderWindow& window) {
	for (int i = 0; i < 64; i++) {
		if ((board.Occupancy >> i) & 1) {
			if ((board.Types[0] >> i) & 1)((board.colours[0] >> i )& 1) ? draw(window, i, 0, 0) : draw(window, i, 1, 0);
			if ((board.Types[2] >> i) & 1)(board.colours[0] >> i) & 1 ? draw(window, i, 0, 2) : draw(window, i, 1, 2);
			if ((board.Types[1] >> i) & 1)(board.colours[0] >> i) & 1 ? draw(window, i, 0, 1) : draw(window, i, 1, 1);
			if ((board.Types[3] >> i) & 1)(board.colours[0] >> i) & 1 ? draw(window, i, 0, 3) : draw(window, i, 1, 3);
			if ((board.Types[4] >> i) & 1)(board.colours[0] >> i) & 1 ? draw(window, i, 0, 4) : draw(window, i, 1, 4);
			if ((board.Types[5] >> i) & 1)(board.colours[0] >> i) & 1 ? draw(window, i, 0, 5) : draw(window, i, 1, 5);
		}
	}
}

void chess_pattern(sf::RenderWindow& window, sf::RectangleShape White_square, sf::RectangleShape Black_square) {
	for (int i = 0; i < 64; i++) {
		int y = floor(i / 8);
		int x = i - y * 8;
		if ((x + y) % 2 == 0) {
			White_square.setPosition(x * 150, y * 150);
			window.draw(White_square);
		}
		else {
			Black_square.setPosition(x * 150, y * 150);
			window.draw(Black_square);
		}
	}
}

sf::Vector2i move_piece(sf::RenderWindow& window, sf::RectangleShape White_square, sf::RectangleShape Black_square,int movedpiece,int colour) {
	bool notdone = true;
	sf::Vector2i position = sf::Mouse::getPosition(window);
	while (notdone) {
		chess_pattern(window, White_square, Black_square);
		draw_board(window);
		sf::Vector2i position = sf::Mouse::getPosition(window);
		draw2(window,position.x, position.y, colour,movedpiece-6*colour);
		window.display();
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i position = sf::Mouse::getPosition(window);
					notdone = false;
					return position;
				}
			}
		}
	}
}

void print_piece_info() {
	std::cout << "o:" << popCount64bit(board.Occupancy) << std::endl;
	std::cout << "p:" << popCount64bit(board.Types[0]) << std::endl;
	std::cout << "n:" << popCount64bit(board.Types[1]) << std::endl;
	std::cout << "b:" << popCount64bit(board.Types[2]) << std::endl;
	std::cout << "r:" << popCount64bit(board.Types[3]) << std::endl;
	std::cout << "q:" << popCount64bit(board.Types[4]) << std::endl;
	std::cout << "k:" << popCount64bit(board.Types[5]) << std::endl;
	std::cout << "w:" << popCount64bit(board.colours[0]) << std::endl;
	std::cout << "b:" << popCount64bit(board.colours[1]) << std::endl;
}


void update_graphics() {
	window.clear();
	chess_pattern(window, White_square, Black_square);
	draw_board(window);
	window.display();
}
void end_game(bool win) {
	sf::Text text;
	sf::Font font;
	if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
		// Handle font loading error
		printf("FAILURE TO LOAD FONT");
		exit(-1);
	}
	text.setFont(font);
	if (win) {
		text.setString("You Won!");
	}
	else
	{
		text.setString("You Lost!");
	}
	text.setCharacterSize(250);
	text.setFillColor(sf::Color::Red);
	update_graphics();
	window.draw(text);
	window.display();

}

bool turn() {
	std::vector<Move> Moves;
	GenerateLegalMoves(colour, Moves);
	if (Moves.empty()) {
		return true;
	}
	update_graphics();
	if (((your_colour == colour) or 0) and 0) {
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
				update_graphics();
			}
			delete position;
		}
	}
	else {
		sf::Event events;
		window.pollEvent(events);
		make_move(*ai(1000, colour), colour);
		update_graphics();
	}

	return false;
}

void run_game() {
	bool game_over = false;
	while (!game_over) {
		if (colour) {
			colour = 0;
		}
		else {
			colour = 1;
		}
		game_over = turn();
	}
	
	end_game(colour != your_colour);
	std::chrono::milliseconds duration(1000);
	std::this_thread::sleep_for(duration);
	while (true){}
}
