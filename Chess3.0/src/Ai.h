#pragma once
#include "Evaluation.h"
#include "Moves.h"
#include "Graphics.h"
#include <chrono>
#include <algorithm>
#include <thread>
#include <iostream>

int MinMax(int depth, bool colour, bool first, int alpha, int beta, sf::RenderWindow& window, sf::RectangleShape White_square, sf::RectangleShape Black_square);

Move* ai(int depth, bool colour, sf::RenderWindow& window, sf::RectangleShape White_square, sf::RectangleShape Black_square);