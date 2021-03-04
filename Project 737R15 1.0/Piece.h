#pragma once
#include "BG.h"
#include "GameCursor.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>

class Piece{
private:
	int** field;
	sf::Color color;
	int type;
	int fieldX;
	int fieldY;
public:
	Piece(sf::Color color, int type, int** field, int fieldX, int fieldY);
	int** getField();
};

