#pragma once
#include "controller.h"
#include "playerKB.h"
#include "playermouse.h"
#include "ai.h"
#include "controllerSetup.h"
#include "mainMenu.h"
#include "gameState.h" //needed for enum items
#include "game.h"
#include <sfml/Graphics.hpp>
#include <cassert>

class InputSettings {

public:
	InputSettings() = delete;
	InputSettings(sf::RenderWindow& window) : m_window(window) {}
	ControllerSetup getControllerSettings(Controls c, bool player1) {
		if (c == Controls::KB) {
			return ControllerSetup{ c, general, PlayerKBSetupParams{sf::Keyboard::W, sf::Keyboard::S} };
		}
		else if (c == Controls::MOUSE) {
			return  ControllerSetup{ c, general, PlayerMouseParams{m_window} };
		}
		else if (c == Controls::AI) {
			return ControllerSetup{ c, general, AISetupParams{player1 ? items::P1 : items::P2} };
		}
		else {
			assert(false);
			return ControllerSetup{ c, general, AISetupParams{items::P1} };
		}

	}
private:
	sf::RenderWindow& m_window;
	ControllerSettings general{ 250.0 };
};