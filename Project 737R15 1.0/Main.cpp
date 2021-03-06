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


/*int controlsMenu(const int& sizeX, const int& sizeY, RenderWindow& window, BG& background, GameCursor& mouse, Keyboard::Key leftKey, Keyboard::Key rightKey, Keyboard::Key speedUpKey, Keyboard::Key rotateKey) {
	vector <Button> buttons;
	bool oneSelected = false;

	Button leftButton(100, 35, sizeX / 2, 850, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255), "LEFT KEY: " + leftKey, window, defaultFont);
	Button rightButton(100, 35, sizeX / 2, 850, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255), "RIGHT KEY: " + rightKey, window, defaultFont);
	Button rotateButton(100, 35, sizeX / 2, 850, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255), "ROTATE KEY: " + rotateKey, window, defaultFont);
	Button speedUpButton(100, 35, sizeX / 2, 850, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255), "SPEED UP KEY: " + speedUpKey, window, defaultFont);

	buttons.push_back(leftButton);
	buttons.push_back(rightButton);
	buttons.push_back(rotateButton);
	buttons.push_back(speedUpButton);

	while (window.isOpen())
	{
		Event event;

		window.clear(Color(0, 0, 0));

		while (window.pollEvent(event))
		{
			event_handler(event, window, mouse, buttons, oneSelected);
			window.setMouseCursor(mouse.getCursor());
		}

		background.draw();

		window.display();
	}
}*/


ExitCode settings(RenderWindow& window, BG& background, GameCursor& mouse, int& musicVolume, map<string, Keyboard::Key>& keys)
{
	const int MaxChangeSpeed = 10;
	bool oneSelected = false;
	bool oneClicked = false;
	int ChangeTime = MaxChangeSpeed;
	int timePassed = 0;
	bool waitingForInput = false;
	int rebindedKey = -1; //leftKey = 0, rightKey = 1, speedUpKey = 2, rotateKey = 3
	vector <Button*> buttons;

	//Button volumeButton(float(window.getSize().x) / 2.f, float(window.getSize().y) / 2.f + 100.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255), "MUSIC VOLUME " + to_string(musicVolume), window, defaultFont, true);
	Button applyButton(float(window.getSize().x) / 2.f, float(window.getSize().y) - 150.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255), "APPLY", window, defaultFont, true);
	Button backButton(float(window.getSize().x) / 2.f, float(window.getSize().y) - 50.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255), "BACK", window, defaultFont, true);
	Button redButton(float(window.getSize().x) / 2.f, float(window.getSize().y) / 2.f + 100.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255), 
		"RED COLOR: " + (keyToString.at(keys.at("red"))), window, defaultFont, true);

	buttons.push_back(&backButton);
	buttons.push_back(&applyButton);
	buttons.push_back(&redButton);
	//buttons.push_back(&volumeButton);

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
			/*if (waitingForInput && event.type == Event::KeyPressed) {
				switch (rebindedKey) {
					case 0 :
						leftKey = event.key.code;
						leftKeyButton.changeText("MOVE LEFT KEY: " + to_string(event.key.code));
						cout << "CHANGED" << to_string(event.key.code) << endl;
						break;
					case 1:
						rightKey = event.key.code;
						break;
					case 2:
						speedUpKey = event.key.code;
						break;
					case 3:
						rotateKey = event.key.code;
						break;
					default:
						continue;
				}
				rebindedKey = -1;
			}*/

			eventHandler(event, window, mouse, buttons, oneSelected);

			//sliderHandler(window, volumeButton, drawables, "MUSIC VOLUME ", "", 30, musicVolume, 0, 100, 1);

			if (pressCheckChoose(applyButton)) {
				mouse.changeToArrow();
				return ExitCode::Stay;
			}

			else if (pressCheckChoose(backButton))
			{
				backButton.isSelected = false;
				mouse.changeToArrow();
				return ExitCode::BackToRoot;
			}

			else if (pressCheckChoose(redButton)) {
				rebind(window, redButton, keys.at("red"), drawables, "RED COLOR: ");
			}

			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				mouse.changeToArrow();
				return ExitCode::BackToRoot;
			}
		}

		window.setMouseCursor(mouse.getCursor());

		timePassed = 0;
		oneClicked = false;

		redButton.changeText("RED COLOR: " + keys.at("red"));

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
			eventHandler(event, window, mouse, buttons, oneSelected);

			if (pressCheckChoose(mainMenuButton))
			{
				mouse.changeToArrow();
				return ExitCode::BackToRoot;

			}
			else if (pressCheckChoose(retryButton)) {
				mouse.changeToArrow();
				return ExitCode::Play;
			}
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
			eventHandler(event, window, mouse, buttons, oneSelected);

			if (pressCheckChoose(endlessButton) && not inOtherMenu)
			{
				mouse.changeToArrow();
				return ExitCode::Play;
			}

			else if (pressCheckChoose(settingsButton) && not inOtherMenu)
			{
				inOtherMenu = true;
				settingsButton.isSelected = false;
				mouse.changeToArrow();
				return ExitCode::Settings;
			}

			else if (pressCheckChoose(exitButton) && not inOtherMenu)
			{
				window.close();
			}
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

	Music MainMusic;

	if (MainMusic.openFromFile("Main Theme.ogg"))
	{
		MainMusic.play();
		MainMusic.setVolume(1);
		MainMusic.setVolume(float(curMusicVolume));
	}

	bool exit = false;

	while (true)
	{
		switch (mainMenu(window, background, mouse)) {
		case ExitCode::BackToRoot:
			return 0;

		case ExitCode::Settings:
		{	
			while (settings(window, background, mouse, musicVolume, keys) == ExitCode::Stay) {
				curMusicVolume = musicVolume;
				MainMusic.setVolume(float(curMusicVolume));
			}
			 
			musicVolume = curMusicVolume;
			break;
		}
		case ExitCode::Play:
			exit = false;

			while (!exit && difficultyMenu(window, mouse, background, parameters) == ExitCode::Play) {
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
