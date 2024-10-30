#include "options.h"

/** @cond */
#include <iostream>
#include <cassert>
/** @endcond */


OptionsMenu::OptionsMenu(sf::RenderWindow& window, const Options& options) : m_window(window), m_options(options), m_highlighted(0) {
	assert(m_font.loadFromFile("arial.ttf") && "Font not found");
	for (int i = 0; i < 3; ++i) {
		sf::Text text;
		text.setFont(m_font);
		text.setString(std::to_string(i));
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::White);
		text.setPosition(50, 50 + i * 30);
		m_menuTexts.push_back(text);
	}
}



bool OptionsMenu::update(const std::vector<sf::Event>& events) {
	for (const auto& event : events) {
		if (event.type == sf::Event::KeyPressed) {
			if (handleKey(event)) {
				return true;
			}
		}
	}
	display();
	return false;
}

bool OptionsMenu::handleKey(sf::Event event) {
	switch (event.key.code) {
	case sf::Keyboard::Down:
		m_highlighted += 1;
		if (m_highlighted >= m_options.element_count) {
			m_highlighted = 0;
		}
		break;
	case sf::Keyboard::Up:
		m_highlighted -= 1;
		if (m_highlighted < 0) {
			m_highlighted = m_options.element_count - 1;
		}
		break;
	case sf::Keyboard::Left:
		assert(m_highlighted < m_options.element_count && m_highlighted >= 0);
		if (m_highlighted == 0) {
			m_options.player1Size -= 5.0;
		}
		if (m_highlighted == 1) {
			m_options.player2Size -= 5.0;
		}
		if (m_highlighted == 2) {
			m_options.ballVelocity -= 5;
			if (m_options.ballVelocity < 0) {
				m_options.ballVelocity = 0;
			}
		}
		break;
	case sf::Keyboard::Right:
		assert(m_highlighted < m_options.element_count && m_highlighted >= 0);
		if (m_highlighted == 0) {
			m_options.player1Size += 5.0;
		}
		if (m_highlighted == 1) {
			m_options.player2Size += 5.0;
		}
		if (m_highlighted == 2) {
			m_options.ballVelocity += 5;
		}
		break;
	case sf::Keyboard::Return:
			return true;
		break;
	}
	return false;
}

void OptionsMenu::display() {
	m_window.clear();
	updateTexts();
	m_window.display();
}

void OptionsMenu::updateTexts() {
	m_menuTexts[0].setString("Player 1 size: " + std::to_string(m_options.player1Size));
	m_menuTexts[0].setFillColor(m_highlighted == 0 ? sf::Color::Red : sf::Color::White);
	m_menuTexts[1].setString("Player 2 size: " + std::to_string(m_options.player2Size));
	m_menuTexts[1].setFillColor(m_highlighted == 1 ? sf::Color::Red : sf::Color::White);
	m_menuTexts[2].setString("Ball velocity: " + std::to_string(m_options.ballVelocity));
	m_menuTexts[2].setFillColor(m_highlighted == 2 ? sf::Color::Red : sf::Color::White);

	for (const auto& text : m_menuTexts) {
		m_window.draw(text);
	}
}