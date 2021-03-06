#include "GameCursor.h"


GameCursor::GameCursor() {
	cursor.loadFromSystem(sf::Cursor::Arrow);
	color = GameColor::White;
	size = 26;
}

void GameCursor::changeToHand() {
	cursor.loadFromSystem(sf::Cursor::Hand);
}

void GameCursor::changeToArrow() {
	cursor.loadFromSystem(sf::Cursor::Arrow);
}

void GameCursor::setCursor(GameColor color) {
	this->color = color;
	sf::Image texture;
	switch (color) {
	case GameColor::Red:
		texture.loadFromFile("cursor_red2.png");
		cursor.loadFromPixels(texture.getPixelsPtr(), sf::Vector2u(size, size), sf::Vector2u(size/2, size / 2));
		break;
	case GameColor::Blue:
		texture.loadFromFile("cursor_blue2.png");
		cursor.loadFromPixels(texture.getPixelsPtr(), sf::Vector2u(size, size), sf::Vector2u(size / 2, size / 2));
		break;
	case GameColor::Green:
		texture.loadFromFile("cursor_green2.png");
		cursor.loadFromPixels(texture.getPixelsPtr(), sf::Vector2u(size, size), sf::Vector2u(size / 2, size / 2));
		break;
	case GameColor::Yellow:
		texture.loadFromFile("cursor_yellow2.png");
		cursor.loadFromPixels(texture.getPixelsPtr(), sf::Vector2u(size, size), sf::Vector2u(size / 2, size / 2));
		break;
	}
}

sf::Cursor& GameCursor::getCursor() {
	return cursor;
}

sf::Vector2f GameCursor::getPos(sf::RenderWindow& window) {
	return window.mapPixelToCoords(mouse.getPosition(window));
}

GameColor GameCursor::getColor() {
	return color;
}
