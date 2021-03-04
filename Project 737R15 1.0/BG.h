#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "DrawableObj.h"

class BG : public DrawableObj
{
private:
	sf::RenderWindow& window;
	sf::RectangleShape bg;
	float winWidth;
	float winHeight;
	sf::Texture texture;
	std::string fileName;

public:
	BG(float winWidth, float winHeight, sf::RenderWindow& window, std::string fileName, sf::IntRect textureRect);
	BG(const BG& BGcopy);
	void drawObj();
};

