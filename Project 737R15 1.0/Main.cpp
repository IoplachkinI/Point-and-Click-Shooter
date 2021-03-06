#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <math.h>
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


ExitCode settings(RenderWindow& window, BG& background, GameCursor& mouse, int& musicVolume)
{
	const int MaxChangeSpeed = 10;
	bool oneSelected = false;
	bool oneClicked = false;
	int ChangeTime = MaxChangeSpeed;
	int timePassed = 0;
	bool waitingForInput = false;
	int rebindedKey = -1; //leftKey = 0, rightKey = 1, speedUpKey = 2, rotateKey = 3
	vector <Button*> buttons;

	Button volumeButton(float(window.getSize().x) / 2.f, float(window.getSize().y) / 2.f + 100.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255), "MUSIC VOLUME " + to_string(musicVolume), window, defaultFont, true);
	Button applyButton(float(window.getSize().x) / 2.f, float(window.getSize().y) - 150.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255), "APPLY", window, defaultFont, true);
	Button backButton(float(window.getSize().x) / 2.f, float(window.getSize().y) - 50.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255), "BACK", window, defaultFont, true);

	buttons.push_back(&backButton);
	buttons.push_back(&applyButton);
	buttons.push_back(&volumeButton);

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

			sliderHandler(window, volumeButton, drawables, "MUSIC VOLUME ", "", 30, musicVolume, 0, 100, 1);

			if (pressCheckChoose(&applyButton)) {
				mouse.changeToArrow();
				return ExitCode::Stay;
			}

			else if (pressCheckChoose(&backButton))
			{
				backButton.isSelected = false;
				mouse.changeToArrow();
				return ExitCode::BackToRoot;
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

			if (pressCheckChoose(&mainMenuButton))
			{
				mouse.changeToArrow();
				return ExitCode::BackToRoot;

			}
			else if (pressCheckChoose(&retryButton)) {
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

			if (pressCheckChoose(&endlessButton) && not inOtherMenu)
			{
				mouse.changeToArrow();
				return ExitCode::Play;
			}

			else if (pressCheckChoose(&settingsButton) && not inOtherMenu)
			{
				inOtherMenu = true;
				settingsButton.isSelected = false;
				mouse.changeToArrow();
				return ExitCode::Settings;
			}

			else if (pressCheckChoose(&exitButton) && not inOtherMenu)
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

	int defaultHealProbability = 5;
	int defaultBombProbability = 5;
	int defaultSpawnRate = 5;
	int defaultStartSpeed = 20;
	int defaultAcceleration = 1;

	parameters["healProb"] = defaultHealProbability;
	parameters["bombProb"] = defaultBombProbability;
	parameters["spawnRate"] = defaultSpawnRate;
	parameters["speed"] = defaultStartSpeed; // MULTIPLY BY -1.f
	parameters["accel"] = defaultAcceleration; // MULTIPLY BY 0.5f

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

	while (true)
	{
		switch (mainMenu(window, background, mouse)) {
		case ExitCode::BackToRoot:
			return 0;

		case ExitCode::Settings:
		{	
			while (settings(window, background, mouse, musicVolume) == ExitCode::Stay) {
				curMusicVolume = musicVolume;
				MainMusic.setVolume(float(curMusicVolume));
			}
			 
			musicVolume = curMusicVolume;
			break;
		}
		case ExitCode::Play:
			if (difficultyMenu(window, mouse, background, parameters) == ExitCode::Play) {
				switch (GameLoop(maxFPS, window, mouse, parameters)) {
				case ExitCode::BackToRoot:
					mouse.changeToArrow();
					break;
				case ExitCode::GameOver:
					while (postGameScreen(window, background, mouse) == ExitCode::Play) {
						GameLoop(maxFPS, window, mouse, parameters);
					};
					break;
				}
			}
			break;

		default:
			return 0;
		}
	}

	mouse.setColor(GameColor::White);
	return 0;
}
