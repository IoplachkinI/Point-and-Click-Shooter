#include "Piece.h"

Piece::Piece(sf::Color color, int type, int** field, int fieldX, int fieldY) {
	if (fieldY > 4 && fieldX > 4) {
		switch (type) {
		case 0:
		{
			field[0][int(fieldX / 2)] = 2;
			field[0][int(fieldX / 2) + 1] = 2;
			field[1][int(fieldX / 2)] = 2;
			field[1][int(fieldX / 2) + 1] = 2;
		}
		break;
		}
	}

	else {
		std::cout << "ERROR: INCORRECT FIELD SIZE" << std::endl;
	}
}

int** Piece::getField() {
	return field;
}