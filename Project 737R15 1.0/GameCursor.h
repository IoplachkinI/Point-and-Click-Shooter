#pragma once
#include <SFML/Graphics.hpp>

enum class GameColor {
	Red,
	Blue,
	Green,
	Yellow,
	White
};

class GameCursor
{
	private:
		sf::Mouse mouse;
		sf::Cursor cursor;
		GameColor color;
		int size;

	public:
		bool LMBalreadyPressed;
		GameCursor();
		void changeToHand();
		void changeToArrow();
		void setCursor(GameColor color);
		sf::Cursor& getCursor();
		sf::Vector2f getPos(sf::RenderWindow& window);
		GameColor getColor();

};

