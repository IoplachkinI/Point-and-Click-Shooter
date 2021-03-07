#include "Handlers.h"


extern const std::map<sf::Keyboard::Key, std::string> keyToString;


int eventHandler(sf::Event& event, sf::RenderWindow& window, GameCursor& mouse, std::vector <Button*>& buttons, bool& oneSelected) //ALWAYS PUT LAST IN EVENT CHECKING CYCLE
{

	switch (event.type)
	{
	case sf::Event::Closed:
	{
		mouse.changeToArrow();
		window.close();
	};
	break;

	case sf::Event::MouseButtonReleased: {
		if (mouse.LMBalreadyPressed && !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			mouse.LMBalreadyPressed = false;
		}
	}

	case sf::Event::MouseButtonPressed: {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			mouse.LMBalreadyPressed = true;
		}
	}

	case sf::Event::MouseMoved: {
		oneSelected = false;
		window.setMouseCursorVisible(true);

		for (int i = 0; i < int(buttons.size()); i++)
		{
			if (buttons[i]->isHoveredOver(mouse.getPos(window)))
			{
				oneSelected = true;
				mouse.changeToHand();
			}
		}
		if (not oneSelected)
		{
			mouse.changeToArrow();
		}
	};
						  break;

	case sf::Event::KeyPressed:
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			window.setMouseCursorVisible(false);
			for (int i = 0; i < int(buttons.size()); i++)
			{
				if (buttons[i]->isSelected && i + 1 < int(buttons.size()))
				{
					buttons[i]->isSelected = false;
					buttons[i + 1]->isSelected = true;
					i++;
				}
			}
			if (not oneSelected) {
				oneSelected = true;
				buttons[0]->isSelected = true;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			window.setMouseCursorVisible(false);
			for (int i = 0; i < int(buttons.size()); i++)
			{
				if (buttons[i]->isSelected && i - 1 >= 0)
				{
					buttons[i]->isSelected = false;
					buttons[i - 1]->isSelected = true;
				}
			}
			if (not oneSelected) {
				oneSelected = true;
				buttons[buttons.size() - 1]->isSelected = true;
			}
		}

	};
	break;
	}

	return 0;
}

bool const pressCheck(Button& button, sf::Keyboard::Key key)
{
	if (button.isSelected &&
		sf::Keyboard::isKeyPressed(key))
	{
		return true;
	}
	return false;

}

bool const pressCheckChoose(Button& button, GameCursor& mouse)
{
	if (button.isSelected &&
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) ||
			(sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
			!mouse.LMBalreadyPressed)))
	{
		mouse.LMBalreadyPressed = true;
		return true;
	}
	return false;
}

bool const pressCheckMouse(Button& button, sf::Mouse::Button key)
{
	if (button.isSelected &&
		sf::Mouse::isButtonPressed(key))
	{
		return true;
	}
	return false;
}

void rebind (sf::RenderWindow& window, Button& button, sf::Keyboard::Key& key, GameCursor& mouse, std::vector<DrawableObj*>& drawables, std::string name, bool& escapePressed){

	button.changeText(name + "???");

	sf::Event event;

	while (true) {
		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::KeyPressed:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
						escapePressed = true;
						return;
					}
					else {
						key = event.key.code;
						button.changeText(name + (keyToString.at(key)));
						return;
					}
					break;
				case sf::Event::MouseButtonReleased:
					if (mouse.LMBalreadyPressed && !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
						mouse.LMBalreadyPressed = false;
					}
			}
		}

		for (auto& drawable : drawables) {
			drawable->drawObj();
		}
		window.display();

	}
}

void sliderHandler(sf::RenderWindow& window, Button& button, std::vector<DrawableObj*>& drawables, std::string name, std::string unit, int changeTime, int& parameter, int lowerThreshold, int upperThreshold, int step) {
	int timePassed = 0;
	bool oneClicked = false;

	while (pressCheck(button, sf::Keyboard::Right)) {
		timePassed++;
		if (not oneClicked && parameter < upperThreshold) {
			parameter += step;
			oneClicked = true;
		}

		if (timePassed >= changeTime && parameter < upperThreshold) {
			timePassed = 0;
			changeTime -= changeTime / 10;
			parameter += step;
		}

		button.changeText(name + std::to_string(parameter) + unit);

		for (DrawableObj* obj : drawables) {
			obj->drawObj();
		}

		window.display();
	}

	oneClicked = false;

	while (pressCheck(button, sf::Keyboard::Left)) {
		timePassed++;
		if (not oneClicked && parameter > lowerThreshold) {
			parameter -= step;
			oneClicked = true;
		}

		if (timePassed >= changeTime && parameter > lowerThreshold){
			timePassed = 0;
			changeTime -= changeTime / 10;
			parameter -= step;
		}

		button.changeText(name + std::to_string(parameter) + unit);

		for (DrawableObj* obj : drawables) {
			obj->drawObj();
		}

		window.display();
	}
}