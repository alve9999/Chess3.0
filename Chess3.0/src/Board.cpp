#include "Board.h"
#include <cstdint>

Board board;

//Method that tells whether a piece exist on a given x,y coordinate
bool Board::GetPosition(int x, int y) {
	return (Board::Occupancy >> (x+8*y)) & 1;
}

//Tells whether a position contains a black piece
bool Board::GetBlack(int x, int y) {
	return (Board::colours[1] >> (x + 8 * y)) & 1;
}

//Tells whether a position contains a white piece
bool Board::GetWhite(int x, int y) {
	return (Board::colours[0] >> (x + 8 * y)) & 1;
}

//Method for ending turn and changing the playing colour
void Board::EndTurn() {
	if (Currentcolour) { Currentcolour = 0; }
	else { Currentcolour = 1; }
}
