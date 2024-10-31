#include "mainMenu.h"

/** @cond */
#include <sfml/Graphics.hpp>
#include <vector>
#include <string>
/** @endcond */

MainMenu::MainMenu(sf::RenderWindow& window) : MenuBase(window, std::vector<std::string>{"Player 1", "Player 2", "Options", "Start"}), m_p1(Controls::KB), m_p2(Controls::KB) {
	m_menuTexts[0].setString("Player 1: " + castEnumToString(m_p1));
	m_menuTexts[1].setString("Player 2: " + castEnumToString(m_p2));
}

int MainMenu::handleKey(sf::Event event) {
    switch (event.key.code) {
    case sf::Keyboard::Left:
        if (highlighted == 0) {
            m_p1 = decrementEnum(m_p1, Controls::COUNT);
			m_menuTexts[0].setString("Player 1: " + castEnumToString(m_p1));
        }
        if (highlighted == 1) {
            m_p2 = decrementEnum(m_p2, Controls::COUNT);
			m_menuTexts[1].setString("Player 2: " + castEnumToString(m_p2));
        }
        break;
    case sf::Keyboard::Right:
        if (highlighted == 0) {
            m_p1 = incrementEnum(m_p1, Controls::COUNT);
            m_menuTexts[0].setString("Player 1: " + castEnumToString(m_p1));
        }
        if (highlighted == 1) {
            m_p2 = incrementEnum(m_p2, Controls::COUNT);
            m_menuTexts[1].setString("Player 2: " + castEnumToString(m_p2));
        }
        break;
    case sf::Keyboard::Return:
        if ((highlighted == 0 && m_p1 != Controls::KB) ||
            (highlighted == 1 && m_p2 != Controls::KB)) {
            break; //does not open any submenu, just stay in MainMenu
        }
        else {
            return highlighted + 1;
        }
        break;
    default:
        break;
    }
    return 0;
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