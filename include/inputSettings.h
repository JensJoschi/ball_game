#pragma once
#include "enums.h"
/** @cond */
#include <cassert>
#include <variant>
#include <SFML/Window.hpp>

/** @endcond */

struct ControllerSettings {
	double sensitivity; /**< Describes how much an object is moved by 1 action call. */
};

struct PlayerMouseParams{
	const sf::Window* m_win;
};

struct PlayerKBSetupParams{
	sf::Keyboard::Key m_upKey;
	sf::Keyboard::Key m_downKey;
};

struct AISetupParams{
	items m_own;
};

using SpecificInput = std::variant<PlayerMouseParams, PlayerKBSetupParams, AISetupParams> ;

struct InputSettings {
	ControllerSettings general;
	SpecificInput specific;
};