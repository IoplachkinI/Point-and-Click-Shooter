#include "Button.h"


Button::Button(float coordX, float coordY, int fontSize, sf::Color color, sf::Color textColor, sf::Color textSelectedColor, std::string str, sf::RenderWindow& window, std::string defaultFont, bool canBeSelected) :
	color(color),
	textColor(textColor),
	textSelectedColor(textSelectedColor),
	str(str),
	window(window),
	isSelected(false),
	canBeSelected(canBeSelected)
{
	pos = sf::Vector2f(coordX, coordY);
	offset = sf::Vector2f(0.f, float(fontSize) / 5.f);

	font.loadFromFile(defaultFont);

	text.setString(str);
	text.setCharacterSize(fontSize);
	text.setFillColor(textColor);
	text.setFont(font);
	textBounds = text.getGlobalBounds();
	text.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
	text.setPosition(pos - offset);

	size = sf::Vector2f(textBounds.width, textBounds.height);

	base.setSize(size);
	base.setOrigin(base.getSize() / 2.f);
	base.setFillColor(color);
	base.setPosition(pos);

};

void Button::drawObj()
{
	//window.draw(base);

	if (isSelected && canBeSelected)
	{
		text.setFillColor(textSelectedColor);
	}
	else {
		text.setFillColor(textColor);
	}

	window.draw(text);
};

void Button::changeText(std::string newStr)
{
	str = newStr;
	text.setString(str);
	textBounds = text.getGlobalBounds();
	text.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
	text.setPosition(pos - offset);
};

bool Button::isHoveredOver(sf::Vector2f position)
{
	if ((abs(pos.x - position.x) <= size.x / 2.0) && (abs(pos.y - position.y) <= size.y / 2.0)) {
		isSelected = true;

	}
	else {
		isSelected = false;
	}
	return isSelected;
};


std::string Button::getStr()
{
	return str;
};


