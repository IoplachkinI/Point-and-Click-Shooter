#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <cmath>
#include <vector>
#include <windows.h>
#include <thread>
#include "BG.h"
#include "Button.h"
#include "GameCursor.h"
#include "Game Process.h"
#include "ExitCode.h"
#include "DifficultyMenu.h"
#include "Handlers.h"


using namespace sf;
using namespace std;


extern const string defaultFont = "18959.ttf";
extern const float tps;
extern const std::map<sf::Keyboard::Key, std::string> keyToString = {
		{sf::Keyboard::A, "A"},
		{sf::Keyboard::B, "B"},
		{sf::Keyboard::C, "C"},
		{sf::Keyboard::D, "D"},
		{sf::Keyboard::E, "E"},
		{sf::Keyboard::F, "F"},
		{sf::Keyboard::G, "G"},
		{sf::Keyboard::H, "H"},
		{sf::Keyboard::I, "I"},
		{sf::Keyboard::J, "J"},
		{sf::Keyboard::K, "K"},
		{sf::Keyboard::L, "L"},
		{sf::Keyboard::M, "M"},
		{sf::Keyboard::N, "N"},
		{sf::Keyboard::O, "O"},
		{sf::Keyboard::P, "P"},
		{sf::Keyboard::Q, "Q"},
		{sf::Keyboard::R, "R"},
		{sf::Keyboard::S, "S"},
		{sf::Keyboard::T, "T"},
		{sf::Keyboard::U, "U"},
		{sf::Keyboard::V, "V"},
		{sf::Keyboard::W, "W"},
		{sf::Keyboard::X, "X"},
		{sf::Keyboard::Y, "Y"},
		{sf::Keyboard::Z, "Z"},
		{sf::Keyboard::Num0, "0"},
		{sf::Keyboard::Num1, "1"},
		{sf::Keyboard::Num2, "2"},
		{sf::Keyboard::Num3, "3"},
		{sf::Keyboard::Num4, "4"},
		{sf::Keyboard::Num5, "5"},
		{sf::Keyboard::Num6, "6"},
		{sf::Keyboard::Num7, "7"},
		{sf::Keyboard::Num8, "8"},
		{sf::Keyboard::Num9, "9"},
		{sf::Keyboard::Escape, "Esc"},
		{sf::Keyboard::LControl, "Control"},
		{sf::Keyboard::LShift, "Shift"},
		{sf::Keyboard::LAlt, "Alt"},
		{sf::Keyboard::LSystem, "Window"},
		{sf::Keyboard::RControl, "Right Control"},
		{sf::Keyboard::RShift, "Right Shift"},
		{sf::Keyboard::RAlt, "Right Alt"},
		{sf::Keyboard::RSystem, "Right Window"},
		{sf::Keyboard::Menu, "Menu"},
		{sf::Keyboard::LBracket, "["},
		{sf::Keyboard::RBracket, "]"},
		{sf::Keyboard::Semicolon, ";"},
		{sf::Keyboard::Comma, ","},
		{sf::Keyboard::Period, "."},
		{sf::Keyboard::Quote, "'"},
		{sf::Keyboard::Slash, "/"},
		{sf::Keyboard::Backslash, "\\"},
		{sf::Keyboard::Tilde, "~"},
		{sf::Keyboard::Equal, "="},
		{sf::Keyboard::Hyphen, "-"},
		{sf::Keyboard::Space, "Space"},
		{sf::Keyboard::Enter, "Enter"},
		{sf::Keyboard::Backspace, "Backspace"},
		{sf::Keyboard::Tab, "Tab"},
		{sf::Keyboard::PageUp, "Page up"},
		{sf::Keyboard::PageDown, "Page down"},
		{sf::Keyboard::End, "End"},
		{sf::Keyboard::Home, "Home"},
		{sf::Keyboard::Insert, "Insert"},
		{sf::Keyboard::Delete, "Delete"},
		{sf::Keyboard::Add, "+"},
		{sf::Keyboard::Subtract, "-"},
		{sf::Keyboard::Multiply, "*"},
		{sf::Keyboard::Divide, "/"},
		{sf::Keyboard::Left, "Left arrow"},
		{sf::Keyboard::Right, "Right arrow"},
		{sf::Keyboard::Up, "Up arrow"},
		{sf::Keyboard::Down, "Down arrow"},
		{sf::Keyboard::Numpad0, "0 (Numpad)"},
		{sf::Keyboard::Numpad1, "1 (Numpad)"},
		{sf::Keyboard::Numpad2, "2 (Numpad)"},
		{sf::Keyboard::Numpad3, "3 (Numpad)"},
		{sf::Keyboard::Numpad4, "4 (Numpad)"},
		{sf::Keyboard::Numpad6, "5 (Numpad)"},
		{sf::Keyboard::Numpad6, "6 (Numpad)"},
		{sf::Keyboard::Numpad7, "7 (Numpad)"},
		{sf::Keyboard::Numpad8, "8 (Numpad)"},
		{sf::Keyboard::Numpad9, "9 (Numpad)"},
		{sf::Keyboard::F1, "F1"},
		{sf::Keyboard::F2, "F2"},
		{sf::Keyboard::F3, "F3"},
		{sf::Keyboard::F4, "F4"},
		{sf::Keyboard::F5, "F5"},
		{sf::Keyboard::F6, "F6"},
		{sf::Keyboard::F7, "F7"},
		{sf::Keyboard::F8, "F8"},
		{sf::Keyboard::F9, "F9"},
		{sf::Keyboard::F10, "F10"},
		{sf::Keyboard::F11, "F11"},
		{sf::Keyboard::F12, "F12"},
		{sf::Keyboard::F13, "F13"},
		{sf::Keyboard::F14, "F14"},
		{sf::Keyboard::F15, "F15"},
		{sf::Keyboard::Pause, "Pause" }
};


ExitCode settings(RenderWindow& window, BG& background, GameCursor& mouse, int& musicVolume, map<string, Keyboard::Key>& keys)
{
	bool oneSelected = false;
	bool oneClicked = false;
	bool escapeAlreadyPressed = false;
	vector <Button*> buttons;

	Button backButton(float(window.getSize().x) / 2.f, float(window.getSize().y) - 75.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255), "BACK", window, defaultFont, true);
	Button redButton(float(window.getSize().x) / 2.f, float(window.getSize().y) / 2.f - 100.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255), 
		"RED COLOR: " + (keyToString.at(keys.at("red"))), window, defaultFont, true);
	Button blueButton(float(window.getSize().x) / 2.f, float(window.getSize().y) / 2.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255),
		"BLUE COLOR: " + (keyToString.at(keys.at("blue"))), window, defaultFont, true);
	Button greenButton(float(window.getSize().x) / 2.f, float(window.getSize().y) / 2.f + 100.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255),
		"GREEN COLOR: " + (keyToString.at(keys.at("green"))), window, defaultFont, true);
	Button yellowButton(float(window.getSize().x) / 2.f, float(window.getSize().y) / 2.f + 200.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255),
		"YELLOW COLOR: " + (keyToString.at(keys.at("yellow"))), window, defaultFont, true);

	buttons.push_back(&backButton);
	buttons.push_back(&redButton);
	buttons.push_back(&blueButton);
	buttons.push_back(&greenButton);
	buttons.push_back(&yellowButton);

	vector<DrawableObj*> drawables;
	drawables.push_back(&background);
	for (int i = 0; i < int(buttons.size()); i++) {
		drawables.push_back(buttons[i]);
	}

	while (window.isOpen())
	{
		Event event;

		window.clear(Color(0, 0, 0));

		while (window.pollEvent(event)) 
		{
			switch (event.type) {
				case Event::KeyReleased:
					if (escapeAlreadyPressed && !Keyboard::isKeyPressed(Keyboard::Escape)) {
						escapeAlreadyPressed = false;
					}
					break;
			}

			if (pressCheckChoose(backButton, mouse))
			{
				mouse.changeToArrow();
				return ExitCode::BackToRoot;
			}

			else if (pressCheckChoose(redButton, mouse)) {
				rebind(window, redButton, keys.at("red"), mouse, drawables, "RED COLOR: ", escapeAlreadyPressed);
				redButton.isSelected = false;
				oneSelected = false;
				mouse.changeToArrow();
			}
			else if (pressCheckChoose(blueButton, mouse)) {
				rebind(window, redButton, keys.at("blue"), mouse, drawables, "BLUE COLOR: ", escapeAlreadyPressed);
				redButton.isSelected = false;
				oneSelected = false;
				mouse.changeToArrow();
			}
			else if (pressCheckChoose(greenButton, mouse)) {
				rebind(window, redButton, keys.at("green"), mouse, drawables, "GREEN COLOR: ", escapeAlreadyPressed);
				redButton.isSelected = false;
				oneSelected = false;
				mouse.changeToArrow();
			}
			else if (pressCheckChoose(yellowButton, mouse)) {
				rebind(window, redButton, keys.at("yellow"), mouse, drawables, "YELLOW COLOR: ", escapeAlreadyPressed);
				redButton.isSelected = false;
				oneSelected = false;
				mouse.changeToArrow();
			}

			if (Keyboard::isKeyPressed(Keyboard::Escape) && !escapeAlreadyPressed)
			{
				mouse.changeToArrow();
				return ExitCode::BackToRoot;
			}

			eventHandler(event, window, mouse, buttons, oneSelected);
		}

		window.setMouseCursor(mouse.getCursor());

		oneClicked = false;

		redButton.changeText("RED COLOR: " + keyToString.at(keys.at("red")));

		for (DrawableObj* obj : drawables) {
			obj->drawObj();
		}

		window.display();

	}
	return ExitCode::BackToRoot;
}


ExitCode postGameScreen(RenderWindow& window, BG& background, GameCursor& mouse) {

	bool oneSelected = false;

	vector <Button*> buttons;

	Button gameOverSign(float(window.getSize().x) / 2.f, float(window.getSize().y) / 2.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255), "GAME OVER", window, defaultFont, true);
	Button retryButton(float(window.getSize().x) / 2.f, float(window.getSize().y) / 2.f + 100.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255), "RETRY", window, defaultFont, true);
	Button mainMenuButton(float(window.getSize().x) / 2.f, float(window.getSize().y) / 2.f + 200.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255), "MAIN MENU", window, defaultFont, true);

	buttons.push_back(&mainMenuButton);
	buttons.push_back(&retryButton);

	vector<DrawableObj*> drawables;
	drawables.push_back(&background);
	for (int i = 0; i < int(buttons.size()); i++) {
		drawables.push_back(buttons[i]);
	}
	drawables.push_back(&gameOverSign);

	while (window.isOpen()){
		Event event;

		window.clear(Color(0, 0, 0));

		while (window.pollEvent(event)) {
			if (pressCheckChoose(mainMenuButton, mouse))
			{
				mouse.changeToArrow();
				return ExitCode::BackToRoot;

			}
			else if (pressCheckChoose(retryButton, mouse)) {
				mouse.changeToArrow();
				return ExitCode::Play;
			}

			eventHandler(event, window, mouse, buttons, oneSelected);
		}

		window.setMouseCursor(mouse.getCursor());

		for (DrawableObj* obj : drawables) {
			obj->drawObj();
		}

		window.display();

	}

	return ExitCode::BackToRoot;
}


ExitCode mainMenu(RenderWindow& window, BG& background, GameCursor& mouse)
{

	bool inOtherMenu = false;
	bool oneSelected = false;

	vector <Button*> buttons;
	Button endlessButton(float(window.getSize().x) / 2.f, float(window.getSize().y) / 2.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255), "ENDLESS", window, defaultFont, true);
	Button settingsButton(float(window.getSize().x) / 2.f, float(window.getSize().y) / 2.f + 100.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255), "SETTINGS", window, defaultFont, true);
	Button exitButton(float(window.getSize().x) / 2.f, float(window.getSize().y) / 2.f + 200.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255), "EXIT", window, defaultFont, true);
	buttons.push_back(&exitButton);
	buttons.push_back(&settingsButton);
	buttons.push_back(&endlessButton);

	vector<DrawableObj*> drawables;
	drawables.push_back(&background);
	for (int i = 0; i < int(buttons.size()); i++) {
		drawables.push_back(buttons[i]);
	}

	while (window.isOpen()) 
	{
		Event event;

		window.clear(Color(0, 0, 0));

		while (window.pollEvent(event)) {

			if (pressCheckChoose(endlessButton, mouse) && not inOtherMenu)
			{
				mouse.changeToArrow();
				return ExitCode::Play;
			}

			else if (pressCheckChoose(settingsButton, mouse) && not inOtherMenu)
			{
				inOtherMenu = true;
				settingsButton.isSelected = false;
				mouse.changeToArrow();
				return ExitCode::Settings;
			}

			else if (pressCheckChoose(exitButton, mouse) && not inOtherMenu)
			{
				window.close();
			}

			eventHandler(event, window, mouse, buttons, oneSelected);
		}

		window.setMouseCursor(mouse.getCursor());

		for (int i = 0; i < int(drawables.size()); i++) {
			drawables[i]->drawObj();
		}

		window.display();

	}
	return ExitCode::BackToRoot;
}



int main() {
	srand(unsigned int(time(0)));
	const int sizeX = 900;
	const int sizeY = 900;
	const int maxFPS =  0;
	int musicVolume = 0;
	int curMusicVolume = musicVolume;
	map <string, int> parameters;
	map <string, Keyboard::Key> keys;

	parameters["healProb"] = 5;
	parameters["bombProb"] = 5;
	parameters["spawnRate"] = 5;
	parameters["speed"] = 20; // MULTIPLY BY -1.f
	parameters["accel"] = 1; // MULTIPLY BY 0.5f

	keys["red"] = Keyboard::Key::Num1;
	keys["blue"] = Keyboard::Key::Num2;
	keys["green"] = Keyboard::Key::Num3;
	keys["yellow"] = Keyboard::Key::Num4;

	RenderWindow window(VideoMode(sizeX, sizeY), "Shooter", Style::Close);
	window.setFramerateLimit(maxFPS);
	//window.setVerticalSyncEnabled(true);

	BG background(sizeX, sizeY, window, "menu_background.png", IntRect(sf::Vector2i(20, 0), sf::Vector2i(184, 210)));

	GameCursor mouse;

	bool exit = false;

	while (true)
	{
		switch (mainMenu(window, background, mouse)) {
		case ExitCode::BackToRoot:
			return 0;

		case ExitCode::Settings:
		{
			mouse.LMBalreadyPressed = true;
			settings(window, background, mouse, musicVolume, keys);
			break;
		}
		case ExitCode::Play:
			exit = false;

			while (!exit && difficultyMenu(window, mouse, background, parameters) == ExitCode::Play) {
				mouse.LMBalreadyPressed = false;
					switch (GameLoop(maxFPS, window, mouse, parameters, keys)) {
						case ExitCode::BackToRoot:
							mouse.changeToArrow();
							exit = true;
							break;
						case ExitCode::GameOver:
							if (postGameScreen(window, background, mouse) == ExitCode::BackToRoot) {
								exit = true;
							}
							break;
					}
			}
			break;

		default:
			return 0;
		}
	}

	mouse.changeToArrow();
	return 0;
}
