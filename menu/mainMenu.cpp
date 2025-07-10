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
	//highlight id follows menu items: 0= p1, 1= p2, 2= options, 3= start
    switch (event.key.code) {
    case sf::Keyboard::Left: //switch player 1/2 control
        if (highlighted == 0) {
            m_p1 = decrementEnum(m_p1, Controls::COUNT);
            m_menuTexts[0].setString("Player 1: " + castEnumToString(m_p1));
        }
        if (highlighted == 1) {
            m_p2 = decrementEnum(m_p2, Controls::COUNT);
            m_menuTexts[1].setString("Player 2: " + castEnumToString(m_p2));
        }
        break;
    case sf::Keyboard::Right: //switch player 1/2 control
        if (highlighted == 0) {
            m_p1 = incrementEnum(m_p1, Controls::COUNT);
            m_menuTexts[0].setString("Player 1: " + castEnumToString(m_p1));
        }
        if (highlighted == 1) {
            m_p2 = incrementEnum(m_p2, Controls::COUNT);
            m_menuTexts[1].setString("Player 2: " + castEnumToString(m_p2));
        }
        break;
    case sf::Keyboard::Return: //open submenu or start game
        if ((highlighted == 1 && getP1() == Controls::KB) ||
            (highlighted == 2 && getP2() == Controls::KB)) {
                return Windows::KEYBOARD;
        }
        else if (highlighted == 2) { return Windows::OPTIONS; }
        else if (highlighted == 3) { return Windows::START; }
        else { break; } //AI and MOUSE have no submenu yet
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