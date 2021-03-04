#include "DifficultyMenu.h"



using namespace sf;
using namespace std;


extern const string defaultFont;
extern const float tps;


ExitCode difficultyMenu(RenderWindow& window, GameCursor& mouse, BG& bg, map<string, int>& parameters) {
	srand(unsigned int(time(0)));

	bool oneSelected = false;

	vector <Button*> buttons;

	Button backButton (float(window.getSize().x) / 2.f, float(window.getSize().y) - 50.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255), "BACK", window, defaultFont, true);
	Button playButton(float(window.getSize().x) / 2.f, float(window.getSize().y) - 150.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255), "PLAY", window, defaultFont, true);
	Button accelButton(float(window.getSize().x) / 2.f, float(window.getSize().y) / 2.f - 250.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255),
		"ACCELERATION " + to_string(parameters["accel"]), window, defaultFont, true);
	Button speedButton(float(window.getSize().x) / 2.f, float(window.getSize().y) / 2.f - 150.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255),
		"SPEED " + to_string(parameters["speed"]), window, defaultFont, true);
	Button spawnRateButton(float(window.getSize().x) / 2.f, float(window.getSize().y) / 2.f - 50.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255),
		"SPAWN RATE " + to_string(parameters["spawnRate"]), window, defaultFont, true);
	Button bombButton(float(window.getSize().x) / 2.f, float(window.getSize().y) / 2.f + 50.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255),
		"BOMB PROBABILITY " + to_string(parameters["bombProb"]) + " %", window, defaultFont, true);
	Button healButton(float(window.getSize().x) / 2.f, float(window.getSize().y) / 2.f + 150.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255),
		"HEALER PROBABILITY " + to_string(parameters["healProb"]) + " %", window, defaultFont, true);

	buttons.push_back(&backButton);
	buttons.push_back(&playButton);
	buttons.push_back(&healButton);
	buttons.push_back(&bombButton);
	buttons.push_back(&spawnRateButton);
	buttons.push_back(&speedButton);
	buttons.push_back(&accelButton);

	vector<DrawableObj*> drawables;
	drawables.push_back(&bg);
	for (int i = 0; i < int(buttons.size()); i++) {
		drawables.push_back(buttons[i]);
	}

	mouse.changeToArrow();

	while (window.isOpen())
	{
		Event event;

		window.clear(Color(0, 0, 0));

		while (window.pollEvent(event)) {
			eventHandler(event, window, mouse, buttons, oneSelected);
			switch (event.type) {
				case Event::KeyPressed:
					if (Keyboard::isKeyPressed(Keyboard::Escape)) {
						for (int i = 0; i < int(drawables.size()); i++) {
							delete drawables[i];
						}
						return ExitCode::BackToRoot;
					}
			}

			if (pressCheckChoose(buttons[0])) {
				return ExitCode::BackToRoot;
			}
			else if (pressCheckChoose(buttons[1]))
			{
				return ExitCode::Play;
			}
			else {
				sliderHandler(window, healButton, drawables, "HEALER PROBABILITY ", " %", 30, parameters["healProb"], 0, 100 - parameters["bombProb"], 5);
				sliderHandler(window, bombButton, drawables, "BOMB PROBABILITY ", " %", 30, parameters["bombProb"], 0, 100 - parameters["healProb"], 5);
				sliderHandler(window, spawnRateButton, drawables, "SPAWN RATE ", "", 30, parameters["spawnRate"], 1, 20, 1);
				sliderHandler(window, speedButton, drawables, "SPEED ", "", 30, parameters["speed"], 5, 50, 1);
				sliderHandler(window, accelButton, drawables, "ACCELERATION ", "", 30, parameters["accel"], 0, 10, 1);
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