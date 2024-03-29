#include "Game Process.h"
#include <cstdio>
#include <string>
#include <cstdlib>
#include <iostream>
#include "BG.h"
#include "GameCursor.h"
#include <thread>
#include <memory>
#include <vector>
#include <cmath>
#include "Button.h"
#include "Handlers.h"


using namespace std;
using namespace sf;

extern const string defaultFont;
extern const float tps = 20;
extern const map<Keyboard::Key, string> keyToString;
const double millisecPerTick = (double)1000/(double)tps;
const int xSize = 10;
const int ySize = 24;
int x = 0;
int y = 0;


class ColorSelector : public DrawableObj{
private:
	Vector2f size;
	Vector2f pos;
	GameColor color;
	Color outlineColor;
	Texture texture;
	RenderWindow& window;
	RectangleShape object;
	bool isSelected;
	float outlineThickness;

public:

	ColorSelector(float size, float x, float y, float outlineThickness, RenderWindow& window, GameColor color, Color outlineColor) : 
		window (window), 
		outlineThickness(outlineThickness),
		color(color),
		outlineColor(outlineColor)
	{
		this->size = Vector2f(size, size);
		pos = Vector2f(float(x), float(y));
		isSelected = false;

		object.setSize(this->size);
		object.setOrigin(this->size / 2.f);

		object.setOutlineColor(outlineColor);
		object.setPosition(pos);

		switch (color) {
		case GameColor::Red:
			object.setFillColor(Color(255, 0, 0));
			break;
		case GameColor::Blue:
			object.setFillColor(Color(0, 0, 255));
			break;
		case GameColor::Green:
			object.setFillColor(Color(0, 255, 0));
			break;
		case GameColor::Yellow:
			object.setFillColor(Color(255, 186, 0));
			break;
		}
	}

	void deselect() {
		isSelected = false;
		object.setOutlineThickness(0.f);
	}

	GameColor getColor() {
		return color;
	}

	bool select() {
		isSelected = true;
		object.setOutlineThickness(-outlineThickness);
		return isSelected;
	}

	bool getIsSelected() {
		return isSelected;
	}

	void drawObj() {
		window.draw(object);
	}

};


class Heart : public DrawableObj{
private:
	unsigned int stage;
	Vector2f size;
	Vector2f pos;
	Texture texture;
	RenderWindow& window;
	RectangleShape object;


public:

	long long lastAnimationTime;
	bool toAnimate;
	bool toAnimateBackwards;

	Heart(float size, float x, float y, RenderWindow& window, string fileName) : window(window){
		this->size = Vector2f(size, size);
		pos = Vector2f(x, y);
		toAnimate = false;
		toAnimateBackwards = false;
		lastAnimationTime = 0;
		stage = 0;

		if (!texture.loadFromFile(fileName)) {
			throw logic_error("Couldn't open file");
		}

		object.setSize(this->size);
		object.setOrigin(this->size / 2.f);
		object.setPosition(pos);
		object.setTexture(&texture);
		object.setTextureRect(IntRect(Vector2i(0, 0), Vector2i(35, 35)));
	}

	void drawObj() {
		window.draw(object);
	}


	void resetStage() {
		stage = 0;
	}


	int getStage() {
		return stage;
	}


	bool animateBackwards() {
		switch (stage) {
		case 4:
			object.setTextureRect(IntRect(Vector2i(70, 0), Vector2i(35, 35)));
			stage = 3;
			break;
		case 3:
			object.setTextureRect(IntRect(Vector2i(35, 0), Vector2i(35, 35)));
			stage = 2;
			break;
		case 2:
			object.setTextureRect(IntRect(Vector2i(0, 0), Vector2i(35, 35)));
			stage = 1;
			return true;
		default:
			throw logic_error("Wrong stage! ");
		}

		return false;
	}


	bool animate() {
		switch (stage) {
		case 0:
			object.setTextureRect(IntRect(Vector2i(0, 0), Vector2i(35, 35)));
			stage = 1;
			break;
		case 1:
			object.setTextureRect(IntRect(Vector2i(35, 0), Vector2i(35, 35)));
			stage = 2;
			break;
		case 2:
			object.setTextureRect(IntRect(Vector2i(70, 0), Vector2i(35, 35)));
			stage = 3;
			break;
		case 3:
			object.setTextureRect(IntRect(Vector2i(105, 0), Vector2i(35, 35)));
			stage = 4;
			return true;
		default:
			throw logic_error("Wrong stage! ");
		}

		return false;
	}


};


class BasicTarget : public DrawableObj{
protected:
	float interpValue;
	Vector2f pos;
	Vector2f prevPos;
	Texture texture;
	string fileName;
	CircleShape object;
	RenderWindow& window;
	GameColor color;


public:

	bool destroyed;
	bool toDraw;

	void setColor(GameColor color) {
		this->color = color;

		switch (color) {
		case GameColor::Red:
			object.setTexture(&texture);
			object.setTextureRect(IntRect(Vector2i(0, 0), Vector2i(34, 34)));
			break;
		case GameColor::Blue:
			object.setTexture(&texture);
			object.setTextureRect(IntRect(Vector2i(34, 0), Vector2i(34, 34)));
			break;
		case GameColor::Green:
			object.setTexture(&texture);
			object.setTextureRect(IntRect(Vector2i(68, 0), Vector2i(34, 34)));
			break;
		case GameColor::Yellow:
			object.setTexture(&texture);
			object.setTextureRect(IntRect(Vector2i(102, 0), Vector2i(34, 34)));
			break;
		}
	}

	BasicTarget(float r, float x, float y, string fileName, RenderWindow& w, GameColor color) :
		fileName(fileName),
		window(w)
	{
		if (!texture.loadFromFile(fileName)) {
			throw logic_error("Couldn't load texture");
		}
		pos = Vector2f(x, y);
		prevPos = pos;
		object.setRadius(r);
		object.setOrigin(r, r);
		object.setPosition(pos);
		setColor(color);
		toDraw = true;
		destroyed = false;
	}

	void setInterpValue(float interpValue) {
		this->interpValue = interpValue;
	}

	void drawObj() {
		if (toDraw) {
			object.setPosition((pos * interpValue) + (prevPos * (1.f - interpValue)));  //interpolation happens here
			window.draw(object);
		}
	}

	void setPos(Vector2f newPos) {
		object.setPosition(newPos);
		prevPos = pos;
		pos = newPos;
	}

	void setPos(float x, float y) {
		object.setPosition(Vector2f(x, y));
		prevPos = pos;
		pos = Vector2f(x, y);
	}

	float getRadius() {
		return object.getRadius();
	}

	Vector2f getPos() {
		return pos;
	}

	bool compareColor(GameColor color) {
		return this->color == color;
	}

	bool isHoveredOver(GameCursor& mouse) {
		return (sqrt(pow(pos.x - mouse.getPos(window).x, 2) + pow(pos.y - mouse.getPos(window).y, 2)) <= object.getRadius());
	}


	void setPosRand(vector<shared_ptr<BasicTarget>>& targets, int recursionAmount) {
		if (recursionAmount < 10) {
			float assumedX = float(rand() % (window.getSize().x - 2 * int(getRadius())) + getRadius());
			float assumedY = float(window.getSize().y + (rand() % int(object.getRadius())) + object.getRadius());
			for (auto& target : targets) {
				if (target->toDraw && float(sqrt(pow(assumedX - target->getPos().x, 2) + pow(assumedY - target->getPos().y, 2))) <= 2.f * object.getRadius()) {
					recursionAmount++;
					setPosRand(targets, recursionAmount);
					return;
				}
			}

			setPos(assumedX, assumedY);
		}
		else {
			toDraw = false;
		}
		return;
	}

};


class BombTarget : public BasicTarget {
private:
	int bombradius;
	unsigned int stage;
	Texture explosionTexture;
	Sprite sprite;
public:

	long long lastAnimationTime;
	bool toAnimate;

	BombTarget(float r, float x, float y, string fileName, string explosionFileName, RenderWindow& w, GameColor color, int Bombradius) :
		BasicTarget(r, x, y, fileName, w, color), 
		bombradius(Bombradius) 
	{
		if (!explosionTexture.loadFromFile(explosionFileName)) {
			throw logic_error("Couldn't load texture");
		}
		texture.setSmooth(false);
		lastAnimationTime = 0;
		toAnimate = false;
		stage = 0;
		sprite = Sprite(explosionTexture);
		sprite.setOrigin(Vector2f(23.5, 21.5));
		sprite.setScale(float(2 * double(bombradius) / sqrt(2) / 47.0), float(2 * double(bombradius) / sqrt(2) / 43.0));
	}

	int getbombradius() {
		return bombradius;
	}
	
	void setSpritePos(Vector2f newPos) {
		sprite.setPosition(newPos);
	}

	bool animate() {
		switch (stage) {
		case 0:
			sprite.setTextureRect(IntRect(0, 0, 47, 43));
			stage = 1;
			break;
		case 1:
			sprite.setTextureRect(IntRect(47, 0, 47, 43));
			stage = 2;
			break;
		case 2:
			sprite.setTextureRect(IntRect(94, 0, 47, 43));
			stage = 3;
			break;
		case 3:
			sprite.setTextureRect(IntRect(141, 0, 47, 43));
			stage = 4;
			break;
		case 4:
			sprite.setTextureRect(IntRect(188, 0, 47, 43));
			stage = 5;
			break;
		case 5:
			sprite.setTextureRect(IntRect(235, 0, 47, 43));
			stage = 0;
			return true;
		default:
			throw logic_error("Wrong stage! ");
		}

		return false;
}

	void drawSprite() {
		window.draw(sprite);
	}

	Vector2f getSpritePos() {
		return sprite.getPosition();
	}

	void explosion(vector<shared_ptr<BasicTarget>>& targets, unsigned long long &score, int scorePerTarget) {
		for (shared_ptr<BasicTarget>& target : targets) {
			if (sqrt(pow(pos.x - target->getPos().x, 2) + pow(pos.y - target->getPos().y, 2)) <= this->bombradius && target->toDraw) {
				target->toDraw = false;
				target->destroyed = true;
				score += scorePerTarget;
			}
		}
	}
};



class HealTarget : public BasicTarget {
private:
	int livesHealed;

public:

	HealTarget(float r, float x, float y, int livesHealed, string fileName, RenderWindow& w, GameColor color) :
		BasicTarget(r, x, y, fileName, w, color),
		livesHealed(livesHealed) {}

	int heal(int& lives, int maxLives) {
		int healed = 0;

		if (lives + livesHealed > maxLives) {
			lives = maxLives;
			healed = maxLives - lives;
		}
		else {
			lives += livesHealed;
			healed = livesHealed;
		}

		return healed;

	}
};


void deselectOthers(vector<shared_ptr<ColorSelector>>& selectors, int selectedInd) {
	for (int i = 0; i < int(selectors.size()); i++) {
		if (i != selectedInd) {
			selectors[i]->deselect();
		}
	}
};


ExitCode pauseMenu(RenderWindow& window, vector<shared_ptr<DrawableObj>> drawables, GameCursor& mouse) {

	bool oneSelected = false;

	vector <Button*> buttons;
	Button continueButton(float(window.getSize().x) / 2.f, float(window.getSize().y) / 2.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255), "CONTINUE", window, defaultFont, true);
	Button exitButton(float(window.getSize().x) / 2.f, float(window.getSize().y) / 2.f + 100.f, 30, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255), "EXIT", window, defaultFont, true);
	buttons.push_back(&exitButton);
	buttons.push_back(&continueButton);

	while (window.isOpen())
	{
		Event event;

		window.clear(Color(255, 255, 255));

		while (window.pollEvent(event)) {

			if (pressCheckChoose(exitButton, mouse)) {
				mouse.changeToArrow();
				return ExitCode::BackToRoot;
			}
			else if (pressCheckChoose(continueButton, mouse)) {
				mouse.changeToArrow();
				mouse.LMBalreadyPressed = false;
				return ExitCode::Play;
			}

			eventHandler(event, window, mouse, buttons, oneSelected);
		}

		for (int i = 0; i < int(drawables.size()); i++) {
			drawables[i]->drawObj();
		}

		for (auto& button : buttons) {
			button->drawObj();
		}

		window.setMouseCursor(mouse.getCursor());

		window.display();
	}

	return ExitCode::BackToRoot;
};


ExitCode GameLoop(const int maxFPS, sf::RenderWindow& window, GameCursor& mouse, map<string, int>& parameters, map <string, Keyboard::Key> keys)
{
	int ticks = 0;
	int frames = 0;
	int fps = maxFPS;
	int targetAmountCoeff = 2; // 100 / <this value> = actual amount of targets that can be on screen at once

	int spawnProbability = int(tps) / parameters.at("spawnRate") * 4;
	int minSpawnProbability = spawnProbability / 2;
	int healProbability = (parameters.at("healProb") == 0) ? 0 : 100 / parameters.at("healProb");
	int bombProbability = (parameters.at("bombProb") == 0) ? 0 : 100 / parameters.at("bombProb");
	float speed = float(parameters.at("speed") * -1.f);
	int maxLives = 3;
	int animationSwitchTime = 50; // milliseconds
	int clickPeriod = 50; // milliseconds
	int scorePerTarget = int(speed * -2.f) * parameters.at("accel");

	float interpValue = 0.f;
	int lives = maxLives;
	unsigned long long score = 0;
	float sizeCoeff = 20.f;
	bool alreadyClicked = true; // if false - a click on a target will count and it being false represents an actual click

	long long now = std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::steady_clock::now().time_since_epoch()).count();
	long long lastNow = now;
	long long lastTimer = now;
	long long clickTimer = now;

	float xHeart;
	float xColorSelector;

	vector<GameColor> colors = {GameColor::Red, GameColor::Blue, GameColor::Green, GameColor::Yellow};
	vector <shared_ptr<Heart>> hearts;
	vector <shared_ptr<ColorSelector>> colorSelectors(4);
	vector <shared_ptr<BasicTarget>> targets;
	vector <shared_ptr<HealTarget>> healTargets;
	vector <shared_ptr<BombTarget>> bombTargets;
	vector <shared_ptr<DrawableObj>> drawables;

	shared_ptr<Button> scoreButton = make_shared<Button>(window.getSize().x - 175.f, 40.f, 25, Color(0, 0, 0), Color(255, 0, 0), Color(255, 255, 255), "SCORE: ", window, defaultFont, false);
	shared_ptr<BG> background = make_shared<BG>(float(window.getSize().x), float(window.getSize().y), window, "Bg6.jpg", sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(1242, 1242)));

	drawables.push_back(background);

	if (colors.size() % 2 == 0) {
		xColorSelector = float(window.getSize().x) / 2.f - (colors.size() / 2) * (float(window.getSize().x) / sizeCoeff) + (float(window.getSize().x) / sizeCoeff) / 2.f;
	}
	else {
		xColorSelector = window.getSize().x / 2.f - (colors.size() / 2) * (window.getSize().x / sizeCoeff);
	}

	if (lives % 2 == 0){
		xHeart = float(window.getSize().x) / 2.f - (lives / 2) * (float(window.getSize().x) / sizeCoeff) + (float(window.getSize().x) / sizeCoeff) / 2.f;
	}
	else {
		xHeart = float(window.getSize().x) / 2.f - (lives / 2) * (float(window.getSize().x) / sizeCoeff);
	}

	for (int i = 0; i < (100 - parameters.at("healProb") - parameters.at("bombProb")) / targetAmountCoeff; i++) {
		float radius = float(window.getSize().x) / 15.f;
		shared_ptr<BasicTarget> newTarget = make_shared<BasicTarget>(radius, (rand() % (window.getSize().x - 2 * int(radius))) + radius, window.getSize().y + (rand() % long(radius)) + radius,
			"targets.png", window, colors[rand() % colors.size()]);
		targets.push_back(newTarget);
		targets[i]->toDraw = false;
	}

	for (int i = 0; i < parameters.at("healProb") / targetAmountCoeff; i++) {
		float radius = float(window.getSize().x) / 15.f;
		shared_ptr<HealTarget> newTarget = make_shared<HealTarget>(radius, (rand() % (window.getSize().x - 2 * int(radius))) + radius, window.getSize().y + (rand() % long(radius)) + radius, 1,
			"heal_targets.png", window, colors[rand() % colors.size()]);
		newTarget->toDraw = false;
		targets.push_back(newTarget);
		healTargets.push_back(newTarget);
	}

	for (int i = 0; i < parameters.at("bombProb") / targetAmountCoeff; i++) {
		float radius = float(window.getSize().x) / 15.f;
		shared_ptr<BombTarget> newTarget = make_shared<BombTarget>(radius, (rand() % (window.getSize().x - 2 * int(radius))) + radius, window.getSize().y + (rand() % long(radius)) + radius,
			"bomb_targets.png", "explosion.png", window, colors[rand() % colors.size()], 200);
		newTarget->toDraw = false;
		targets.push_back(newTarget);
		bombTargets.push_back(newTarget);
	}

	for (int i = 0; i < int(targets.size()); i++) {
		targets[i]->setPosRand(targets, 0);
		drawables.push_back(targets[i]);
	}

	for (int i = 0; i < int(colorSelectors.size()); i++) {
		shared_ptr<ColorSelector> selector = make_shared<ColorSelector>(float(double(window.getSize().x) / sizeCoeff), xColorSelector, window.getSize().y - window.getSize().x / sizeCoeff, 5.f, window, colors[i], Color(0, 0, 0));
		colorSelectors[i] = selector;
		xColorSelector += window.getSize().x / sizeCoeff;
		drawables.push_back(colorSelectors[i]);
	}

	drawables.push_back(scoreButton);

	colorSelectors[0]->select();
	mouse.setCursor(GameColor::Red);
	window.setMouseCursorVisible(true);

	for (int i = 0; i < lives; i++) {
		shared_ptr<Heart> heart = make_shared<Heart>(window.getSize().x / sizeCoeff, xHeart, window.getSize().x / sizeCoeff, window, "heart.png");
		hearts.push_back(heart);
		xHeart += window.getSize().x / sizeCoeff;
		hearts[i]->animate();
		drawables.push_back(hearts[i]);
	}

	long long cycleStartTime = now;

	while (window.isOpen())
	{

		Event event;

		now = std::chrono::duration_cast<std::chrono::milliseconds>
			(std::chrono::steady_clock::now().time_since_epoch()).count();

		while (window.pollEvent(event)) {
			switch (event.type) {
				case Event::Closed:
					window.close();
					break;
				case Event::MouseLeft:
					mouse.changeToArrow();
					break;
				case Event::MouseEntered:
					mouse.setCursor(mouse.getColor());
					break;
				case Event::LostFocus: {
					mouse.changeToArrow();

					long long lastNowDiff = now - lastNow;
					long long lastTimerDiff = now - lastTimer;

					if (pauseMenu(window, drawables, mouse) == ExitCode::BackToRoot) {
						return ExitCode::BackToRoot;
					}
					
					mouse.setCursor(mouse.getColor());

					now = std::chrono::duration_cast<std::chrono::milliseconds>
						(std::chrono::steady_clock::now().time_since_epoch()).count();
					cycleStartTime = now;
					lastNow = now - lastNowDiff;
					lastTimer = now - lastTimerDiff;
					break;
				}
				case Event::KeyPressed:
					if (Keyboard::isKeyPressed(keys.at("red")) || Keyboard::isKeyPressed(Keyboard::Num1)) {
						mouse.setCursor(GameColor::Red);
						colorSelectors[0]->select();
						deselectOthers(colorSelectors, 0);
					}
					if (Keyboard::isKeyPressed(keys.at("blue")) || Keyboard::isKeyPressed(Keyboard::Num2)) {
						mouse.setCursor(GameColor::Blue);
						colorSelectors[1]->select();
						deselectOthers(colorSelectors, 1);
					}
					if(Keyboard::isKeyPressed(keys.at("green")) || Keyboard::isKeyPressed(Keyboard::Num3)) {
						mouse.setCursor(GameColor::Green);
						colorSelectors[2]->select();
						deselectOthers(colorSelectors, 2);
					}
					if (Keyboard::isKeyPressed(keys.at("yellow")) || Keyboard::isKeyPressed(Keyboard::Num4)) {
						mouse.setCursor(GameColor::Yellow);
						colorSelectors[3]->select();
						deselectOthers(colorSelectors, 3);
					}
					if (Keyboard::isKeyPressed(Keyboard::Escape)) {
						mouse.changeToArrow();

						long long lastNowDiff = now - lastNow;
						long long lastTimerDiff = now - lastTimer;

						if (pauseMenu(window, drawables, mouse) == ExitCode::BackToRoot) {
							return ExitCode::BackToRoot;
						}

						mouse.setCursor(mouse.getColor());

						now = std::chrono::duration_cast<std::chrono::milliseconds>
							(std::chrono::steady_clock::now().time_since_epoch()).count();
						cycleStartTime = now;
						lastNow = now - lastNowDiff;
						lastTimer = now - lastTimerDiff;
					}
					break;
				case Event::MouseButtonPressed:
					if (Mouse::isButtonPressed(Mouse::Left)) {
						clickTimer = now;
						alreadyClicked = false;
					}
			}
		}

		while (now-lastNow >= millisecPerTick && now - cycleStartTime >= 1000) {

			if (rand() % spawnProbability == 0) {
				auto target = targets[rand() % targets.size()];

				if (count_if(targets.begin(), targets.end(), [](auto t) {
					return !t->toDraw;
				}) >= 1) {

					while (true) {
						if (!target->toDraw) {
							target->toDraw = true;
							target->destroyed = false;
							target->setColor(colors[rand() % colors.size()]);
							target->setPosRand(targets, 0);

							if (rand() % 5 == 0 && spawnProbability >= minSpawnProbability) {
								spawnProbability--; //this increases the spawn rate
							}
							break;
						}
						else {
							target = targets[rand() % targets.size()];
						}

					}
				}
			}

			ticks++;

			for (auto& target : targets) {
				if (target->toDraw) {
					if (target->getPos().y < -(target->getRadius())) {
						target->toDraw = false; // a target goes out of bounds and becomes available for a respawn
						if (lives > 0) {
							lives--;
							for (int i = 0; i < int(hearts.size()); i++) {
								if (hearts[i]->getStage() < 4 && !hearts[i]->toAnimate) {
									hearts[i]->toAnimateBackwards = false;
									hearts[i]->toAnimate = true;
									hearts[i]->lastAnimationTime = now;
									if (hearts[i]->animate()) {
										hearts[i]->toAnimate = false;
									}
									break;
								}
							}

						}
						else {
							mouse.changeToArrow();
							window.setMouseCursor(mouse.getCursor());
							return ExitCode::GameOver;
						}
					}

					target->setPos(target->getPos() + Vector2f(0.f, speed));

					if (target->isHoveredOver(mouse) && target->compareColor(mouse.getColor()) && !alreadyClicked) {
						target->toDraw = false;
						target->destroyed = true;
						score += scorePerTarget;
					}
				}
			}

			for (auto& target : healTargets) {
				if (target->destroyed) {
					target->heal(lives, maxLives);
					target->destroyed = false;
					score += scorePerTarget / 2;
					for (int i = hearts.size() - 1; i >= 0; i--) {
						if (hearts[i]->getStage() > 1 && !hearts[i]->toAnimateBackwards) {
							hearts[i]->toAnimateBackwards = true;
							hearts[i]->toAnimate = false;
							hearts[i]->lastAnimationTime = now;
							if (hearts[i]->animateBackwards()) {
								hearts[i]->toAnimateBackwards = false;
							}
							break;
						}
					}
				}
			}

			for (auto& target : bombTargets) {
				if (target->destroyed) {
					target->explosion(targets, score, scorePerTarget);
					target->destroyed = false;
					target->toAnimate = true;
					target->setSpritePos(target->getPos());
					target->animate();
					target->lastAnimationTime = now;
					score += scorePerTarget / 2;
				}
				if (target->toAnimate) {
					target->setSpritePos(target->getSpritePos() + Vector2f(0.f, speed));
				}
			}

			speed -= float(0.01 * float(parameters.at("accel"))); //this increases speed
			interpValue = 0.0;
			lastNow = now;
		}

		try {
			std::this_thread::sleep_for(std::chrono::milliseconds(2));
		}
		catch (int e) {
			cout << "Error: " << e << endl;
		}

		window.setMouseCursor(mouse.getCursor());

		frames++;

		if (now - lastTimer >= 1000 && now - lastTimer <= 1200) {
			//cout << "FPS:" << frames << endl;
			//cout << "TPS:" << ticks << endl;
			fps = frames;
			frames = 0;
			ticks = 0;
			lastTimer = now;
		}

		if (now - clickTimer >= clickPeriod) {
			alreadyClicked = true;
		}

		window.clear(sf::Color(255, 255, 255));

		if (now - cycleStartTime >= 1000) {
			interpValue += float(tps) / float(fps);
		}

		for (int i = 0; i < int(hearts.size()); i++) {
			if (hearts[i]->toAnimate && now - hearts[i]->lastAnimationTime >= animationSwitchTime) {
				hearts[i]->lastAnimationTime = now;
				if (hearts[i]->animate()) {
					hearts[i]->toAnimate = false;
				}
			}
		}

		for (int i = hearts.size() - 1; i >= 0; i--) {
			if (hearts[i]->toAnimateBackwards && now - hearts[i]->lastAnimationTime >= animationSwitchTime) {
				hearts[i]->lastAnimationTime = now;
				if (hearts[i]->animateBackwards()) {
					hearts[i]->toAnimateBackwards = false;
				}
			}
		}

		for (auto& target : bombTargets) {
			if (target->toAnimate && now - target->lastAnimationTime >= animationSwitchTime) {
				target->lastAnimationTime = now;
				if (target->animate()) {
					target->toAnimate = false;
				}
			}
		}

		for (auto& target : targets) {
			target->setInterpValue(interpValue);
		}

		scoreButton->changeText("SCORE: " + to_string(score));

		for (auto& object : drawables) {
			object->drawObj();
		}

		for (auto& target : bombTargets) {
			if (target->toAnimate) {
				target->drawSprite();
			}
		}

		window.display();
	}

	mouse.setCursor(GameColor::White);
	return ExitCode::BackToRoot;
}

int update() {
	return 0;
}

