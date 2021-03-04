#include "BG.h"


BG::BG(float winWidth, float winHeight, sf::RenderWindow& window, std::string fileName, sf::IntRect textureRect) :
	winWidth(winWidth),
	winHeight(winHeight),
	window(window),
	fileName(fileName)
{
	bg.setSize(sf::Vector2f(winWidth, winHeight));
	texture.loadFromFile(fileName);
	bg.setTexture(&texture);
	bg.setTextureRect(textureRect);
}

void BG::drawObj()
{
	window.draw(bg);
}

BG::BG(const BG& BGcopy) : 
	window(BGcopy.window),
	winWidth(BGcopy.winWidth),
	winHeight(BGcopy.winHeight),
	fileName(BGcopy.fileName) {

	bg.setSize(sf::Vector2f(winWidth, winHeight));
	texture.loadFromFile(BGcopy.fileName);
	bg.setTexture(&texture);
}

