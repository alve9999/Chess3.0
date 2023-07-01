#pragma once
#include<SFML/Graphics.hpp>
#include<vector>



void Ginit();

void draw(sf::RenderWindow& window,  int aposition,int colour, int type);

void draw2(sf::RenderWindow& window, int x, int y, int colour, int type);

void draw_board(sf::RenderWindow& window);

void chess_pattern(sf::RenderWindow& window, sf::RectangleShape White_square, sf::RectangleShape Black_square);

sf::Vector2i move_piece(sf::RenderWindow& window, sf::RectangleShape White_square, sf::RectangleShape Black_square, int movedpiece, int colour);

void print_piece_info();

void print_bitboard(uint64_t bitboard);

void imgui_update();

void update_graphics();

void turn();

void run_game();