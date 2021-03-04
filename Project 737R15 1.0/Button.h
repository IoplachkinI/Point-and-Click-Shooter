#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "DrawableObj.h"


class Button : public DrawableObj {
private:
	sf::Vector2f size;
	sf::Vector2f pos;
	sf::Vector2f offset;
	sf::Font font;
	sf::Color color;
	sf::Color textColor;
	sf::Color textSelectedColor;
	std::string str;
	sf::RenderWindow& window;
	sf::RectangleShape base;
	sf::FloatRect textBounds;
	sf::Text text;
	bool canBeSelected;

public:

	bool isSelected;

	Button(float coordX, float coordY, int fontSize, sf::Color color, sf::Color textColor, sf::Color textSelectedColor, std::string str, sf::RenderWindow& window, std::string defaultFont, bool canBeSelected);

	void drawObj();

	void changeText(std::string newStr);

	bool isHoveredOver(sf::Vector2f position);

	std::string getStr();

};

