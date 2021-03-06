#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameCursor.h"
#include "Button.h"
#include "BG.h"

int eventHandler(sf::Event& event, sf::RenderWindow& window, GameCursor& mouse, std::vector <Button*>& buttons, bool& oneSelected);

bool const pressCheck(Button& button, sf::Keyboard::Key key);

bool const pressCheckChoose(Button& button);

bool const pressCheckMouse(Button& button, sf::Mouse::Button key);

void sliderHandler(sf::RenderWindow& window, Button& button, std::vector<DrawableObj*>& drawables, std::string name, std::string unit, int changeTime, int& parameter, int lowerThreshold, int upperThreshold, int step);