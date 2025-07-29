#include "mainMenu.h"
#include "enums.h"
/** @cond */
#include <sfml/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
/** @endcond */

MainMenu::MainMenu(sf::RenderWindow& window, const std::string& fontpath) : 
MenuBase(window, std::vector<std::string>{"Player 1", "Player 2", "Options", "Start"}, Windows::MAIN_MENU, fontpath), 
m_p1(Controls::KB), 
m_p2(Controls::KB) 
{
	m_menuTexts[0].setString("Player 1: " + castEnumToString(Controls::KB));
	m_menuTexts[1].setString("Player 2: " + castEnumToString(Controls::KB));
}

Windows MainMenu::handleKey(sf::Event event) {
    auto handlePlayerInput = [&](int playerIndex, Controls& control) {
        if (event.key.code == sf::Keyboard::Left) {
            control = decrementEnum(control, Controls::COUNT);
            m_menuTexts[playerIndex].setString("Player " + std::to_string(playerIndex + 1) + ": " + castEnumToString(control));
        }
        else if (event.key.code == sf::Keyboard::Right) {
            control = incrementEnum(control, Controls::COUNT);
            m_menuTexts[playerIndex].setString("Player " + std::to_string(playerIndex + 1) + ": " + castEnumToString(control));
        }
        else if (event.key.code == sf::Keyboard::Return) {
            if (control == Controls::KB) {
                return Windows::KEYBOARD;
            } //no mouse or ai window yet
        }
        return defaultReturnVal;
        };

    switch (highlighted) {
        case 0: // Player 1
            return handlePlayerInput(0, m_p1);
        case 1: // Player 2
            return handlePlayerInput(1, m_p2);
		case 2: // Options
            if (event.key.code == sf::Keyboard::Return) {
                return Windows::OPTIONS;
            }
			break;
        case 3: // Start
            if (event.key.code == sf::Keyboard::Return) {
                return Windows::START;
			}
        default:
            break;
    }
    return defaultReturnVal;
}

std::string MainMenu::castEnumToString(Controls c) {
    switch (c) {
    case Controls::KB:
        return "Keyboard";
    case Controls::MOUSE:
        return "Mouse";
    case Controls::AI:
        return "AI";
    default:
        return "Error";
    }
}

Controls MainMenu::getP1() const { return m_p1; }
Controls MainMenu::getP2() const { return m_p2; }
bool MainMenu::isOnP1() const { return highlighted == 0; }