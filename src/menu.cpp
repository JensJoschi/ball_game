#include "menu.h"
#include <sfml/Graphics.hpp>
#include <iostream>
#include <cassert>

Menu::Menu(sf::RenderWindow& window): highlighted(MenuState::P1), m_p1(Controls::KB), m_p2(Controls::KB), m_window(window) {
	assert(m_font.loadFromFile("arial.ttf") && "Font not found");

    // Initialize menu texts
    for (int i = 0; i < static_cast<int>(MenuState::COUNT); ++i) {
        sf::Text text;
        text.setFont(m_font);
        text.setString(castEnumToString(static_cast<MenuState>(i)));
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setPosition(50, 50 + i * 30); // Adjust position as needed
        m_menuTexts.push_back(text);
    }
}

MenuState Menu::update(const std::vector<sf::Event>& events){
    //std::cout << "Menu points at: " << static_cast<int>(highlighted) << std::endl;
    for (const auto& event : events){
        if (event.type == sf::Event::KeyPressed){
            switch (event.key.code){
                case sf::Keyboard::Up:
                    highlighted = decrementEnum(highlighted, MenuState::COUNT);
                    break;
                case sf::Keyboard::Down:
                    highlighted = incrementEnum(highlighted, MenuState::COUNT);
                    break;
                case sf::Keyboard::Left:
                    if (highlighted == MenuState::P1) {
                        m_p1 = decrementEnum(m_p1, Controls::COUNT);
                    }
                    if (highlighted == MenuState::P2) {
                        m_p2 = decrementEnum(m_p2, Controls::COUNT);
                    }
                    break;
                case sf::Keyboard::Right:
                    if (highlighted == MenuState::P1) {
                        m_p1 = incrementEnum(m_p1, Controls::COUNT);
                    }
                    if (highlighted == MenuState::P2) {
                        m_p2 = incrementEnum(m_p2, Controls::COUNT);
                    }
                    break;
                case sf::Keyboard::Return:
                    if ((highlighted == MenuState::P1 && m_p1 != Controls::KB)||
                        (highlighted == MenuState::P2 && m_p2 != Controls::KB)){
                            break; //does not open any submenu, just stay in MainMenu
                        }else {
                            return highlighted;
                        }
                    break;
                default:
                    break;
            }
        }
    }
    display();
    return MenuState::NONE;
}

void Menu::display (){
    m_window.clear();
    drawMenuStateText();
    m_window.display();
}

void Menu::drawMenuStateText(){
    for (int i = 0; i < static_cast<int>(MenuState::COUNT); ++i) {
        std::string text = "";
        if (i == static_cast<int>(MenuState::P1)) {
			text = castEnumToString(m_p1);
        }
		else if (i == static_cast<int>(MenuState::P2)) {
            text = castEnumToString(m_p2);
		}
		m_menuTexts[i].setString(castEnumToString(static_cast<MenuState>(i)) + text);
		sf::Color color = highlighted == static_cast<MenuState>(i) ? sf::Color::Red : sf::Color::White;
		m_menuTexts[i].setFillColor(color);
    }
    for (const auto& text : m_menuTexts) {
        m_window.draw(text);
    }
}
std::string Menu::castEnumToString(Controls c) {
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

std::string Menu::castEnumToString(MenuState c) {
	switch (c) {
	case MenuState::P1:
		return "Player 1";
	case MenuState::P2:
		return "Player 2";
	case MenuState::OPTIONS:
		return "Options";
	case MenuState::START:
		return "Start";
	default:
		return "Error";
	}
}

Controls Menu::getP1() const {return m_p1;}
Controls Menu::getP2() const {return m_p2;}