#pragma once
#include <map>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameCursor.h"
#include "BG.h"
#include "ExitCode.h"
#include "Handlers.h" 


ExitCode difficultyMenu(sf::RenderWindow& window, GameCursor& mouse, BG& bg, std::map<std::string, int>& parameters);

