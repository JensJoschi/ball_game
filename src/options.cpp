#include "options.h"

/** @cond */
#include <iostream>
#include <cassert>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
/** @endcond */


OptionsMenu::OptionsMenu(sf::RenderWindow& window) 
	: MenuBase(window, std::vector<std::string> {
		"Player 1 size: " + std::to_string(Options{}.player1Size),
		"Player 2 size: " + std::to_string(Options{}.player2Size),
		"Ball velocity: " + std::to_string(Options{}.ballVelocity),
		"Back"}), m_options(Options{})
	 {
}

int OptionsMenu::handleKey(sf::Event event) {
	switch (event.key.code) {
	case sf::Keyboard::Left:
		if (highlighted == 0) {
			m_options.player1Size -= 5.0;
		}
		if (highlighted == 1) {
			m_options.player2Size -= 5.0;
		}
		if (highlighted == 2) {
			m_options.ballVelocity -= 5;
			if (m_options.ballVelocity < 0) {
				m_options.ballVelocity = 0;
			}
		}
		break;
	case sf::Keyboard::Right:
		if (highlighted == 0) {
			m_options.player1Size += 5.0;
		}
		if (highlighted == 1) {
			m_options.player2Size += 5.0;
		}
		if (highlighted == 2) {
			m_options.ballVelocity += 5;
		}
		break;
	case sf::Keyboard::Return:
		if (highlighted == 3) return 1;
		break;
	}
	m_menuTexts[0].setString("Player 1 size: " + std::to_string(m_options.player1Size));
	m_menuTexts[1].setString("Player 2 size: " + std::to_string(m_options.player2Size));
	m_menuTexts[2].setString("Ball velocity: " + std::to_string(m_options.ballVelocity));
	return 0;
}

const Options& OptionsMenu::getOptions() const {
	return m_options;
}