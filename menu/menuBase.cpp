#include "menuBase.h"

/** @cond */
#include <sfml/Graphics.hpp>
#include <iostream>
#include <cassert>
#include <vector>
#include <string>
/** @endcond */

MenuBase::MenuBase(sf::RenderWindow& window, const std::vector<std::string>& items, Windows w) : highlighted(0), m_window(window), defaultReturnVal(w) {
    assert(m_font.loadFromFile("arial.ttf") && "Font not found");

    for (int i = 0; i < items.size(); ++i) {
        sf::Text text;
        text.setFont(m_font);
        text.setString(items.at(i));
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setPosition(50, 50 + i * 30);
        m_menuTexts.push_back(text);
    }
}

Windows MenuBase::update(const std::vector<sf::Event>& events) {
    for (const auto& event : events) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                highlighted = (highlighted - 1) % m_menuTexts.size();
            }
            else if (event.key.code == sf::Keyboard::Down) {
                highlighted = (highlighted + 1) % m_menuTexts.size();
            }
            else {
                return(handleKey(event));
            }
        }
    }
    display();
    return defaultReturnVal;
}

void MenuBase::display() {
    m_window.clear();
    highlight();
    m_window.display();
}

void MenuBase::highlight() {
    for (int i = 0; i < m_menuTexts.size(); ++i) {
        if (i == highlighted) {
            m_menuTexts.at(i).setFillColor(sf::Color::Red);
        }
        else {
            m_menuTexts.at(i).setFillColor(sf::Color::White);
        }
        m_window.draw(m_menuTexts.at(i));
    }
}