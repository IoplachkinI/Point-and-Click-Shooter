#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chrono>
#include "GameCursor.h"
#include "ExitCode.h"
#include "BG.h"


ExitCode GameLoop(const int maxFPS, sf::RenderWindow& window, GameCursor& mouse, std::map<std::string, int>& parameters, std::map<std::string, sf::Keyboard::Key> keys);