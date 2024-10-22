#include "menu.h"
#include <sfml/Graphics.hpp>
#include <iostream>

Menu::Menu(sf::RenderWindow& window):highlighted(MenuState::P1), m_p1(Controls::AI), m_p2(Controls::AI) {}

MenuState Menu::update(const std::vector<sf::Event>& events){
    std::cout << "Menu points at: " << static_cast<int>(highlighted) << std::endl;
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
//                        options.setP1(m_p1);
                    }
                    if (highlighted == MenuState::P2) {
                        m_p2 = decrementEnum(m_p2, Controls::COUNT);
//                        options.setP2(m_p2);
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

void Menu::display(){
    std::cout << "Player 1: " << static_cast<int>(m_p1) << std::endl;
    std::cout << "Player 2: " << static_cast<int>(m_p2) << std::endl;
    std::cout << "Highlighted: " << static_cast<int>(highlighted) << std::endl;
}

const Controls& Menu::getP1() const {return m_p1;}
const Controls& Menu::getP2() const {return m_p2;}