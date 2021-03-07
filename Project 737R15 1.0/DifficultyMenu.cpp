#include "DifficultyMenu.h"



using namespace sf;
using namespace std;


extern const string defaultFont;
extern const float tps;


ExitCode difficultyMenu(RenderWindow& window, GameCursor& mouse, BG& bg, map<string, int>& parameters) {
	srand(unsigned int(time(0)));

	bool oneSelected = false;

	vector <Button*> buttons;

	Button backButton (float(window.getSize().x) / 2.f, float(window.getSize().y) - 75.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255), "BACK", window, defaultFont, true);
	Button playButton(float(window.getSize().x) / 2.f, float(window.getSize().y) - 150.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255), "PLAY", window, defaultFont, true);
	Button randButton(float(window.getSize().x) / 2.f, float(window.getSize().y) - 225.f, 20, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255), "RANDOMIZE", window, defaultFont, true);
	Button accelButton(float(window.getSize().x) / 2.f, float(window.getSize().y) / 2.f - 250.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255),
		"ACCELERATION " + to_string(parameters.at("accel")), window, defaultFont, true);
	Button speedButton(float(window.getSize().x) / 2.f, float(window.getSize().y) / 2.f - 150.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255),
		"SPEED " + to_string(parameters.at("speed")), window, defaultFont, true);
	Button spawnRateButton(float(window.getSize().x) / 2.f, float(window.getSize().y) / 2.f - 50.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255),
		"SPAWN RATE " + to_string(parameters.at("spawnRate")), window, defaultFont, true);
	Button bombButton(float(window.getSize().x) / 2.f, float(window.getSize().y) / 2.f + 50.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255),
		"BOMB PROBABILITY " + to_string(parameters.at("bombProb")) + " %", window, defaultFont, true);
	Button healButton(float(window.getSize().x) / 2.f, float(window.getSize().y) / 2.f + 150.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255),
		"HEALER PROBABILITY " + to_string(parameters.at("healProb")) + " %", window, defaultFont, true);

	buttons.push_back(&backButton);
	buttons.push_back(&playButton);
	buttons.push_back(&randButton);
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
			switch (event.type) {
				case Event::KeyPressed:
					if (Keyboard::isKeyPressed(Keyboard::Escape)) {
						return ExitCode::BackToRoot;
					}
			}

			if (pressCheckChoose(backButton, mouse)) {
				return ExitCode::BackToRoot;
			}
			else if (pressCheckChoose(playButton, mouse)){
				return ExitCode::Play;
			}
			else if (pressCheckChoose(randButton, mouse)) {
				parameters.at("healProb") = (rand() % 21) * 5;
				parameters.at("bombProb") = (rand() % (21 - parameters.at("healProb") / 5)) * 5;
				parameters.at("spawnRate") = (rand() % 20) + 1;
				parameters.at("speed") = (rand() % 46) + 5;
				parameters.at("accel") = rand() % 11;

				healButton.changeText("HEALER PROBABILITY " + to_string(parameters.at("healProb")) + " %");
				bombButton.changeText("BOMB PROBABILITY " + to_string(parameters.at("bombProb")) + " %");
				spawnRateButton.changeText("SPAWN RATE " + to_string(parameters.at("spawnRate")));
				speedButton.changeText("SPEED " + to_string(parameters.at("speed")));
				accelButton.changeText("ACCELERATION " + to_string(parameters.at("accel")));
			}
			else {
				sliderHandler(window, healButton, drawables, "HEALER PROBABILITY ", " %", 30, parameters.at("healProb"), 0, 100 - parameters.at("bombProb"), 5);
				sliderHandler(window, bombButton, drawables, "BOMB PROBABILITY ", " %", 30, parameters.at("bombProb"), 0, 100 - parameters.at("healProb"), 5);
				sliderHandler(window, spawnRateButton, drawables, "SPAWN RATE ", "", 30, parameters.at("spawnRate"), 1, 20, 1);
				sliderHandler(window, speedButton, drawables, "SPEED ", "", 30, parameters.at("speed"), 5, 50, 1);
				sliderHandler(window, accelButton, drawables, "ACCELERATION ", "", 30, parameters.at("accel"), 0, 10, 1);
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