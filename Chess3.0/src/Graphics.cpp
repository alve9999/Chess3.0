#include"graphics.h"
#include <SFML/Graphics.hpp>
#include<vector>
#include"Board.h"

std::vector<sf::Sprite> sprites;
std::string sprite_names[] = { "bp.png", "bn.png", "bb.png", "br.png", "bq.png", "bk.png", "wp.png", "wn.png", "wb.png", "wr.png", "wq.png", "wk.png" };
sf::Texture ssprites[12];

void Ginit() {
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