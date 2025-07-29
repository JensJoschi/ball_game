#pragma once
#include "menuBase.h"
/** @cond */
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
/** @endcond */

struct Options {
    float player1Size{ 50.0 };
    float player2Size{ 50.0 };
    int ballVelocity{ 50 };
};

/** @brief OptionsMenu class
 *
 * allows the player to change the game settings such as paddle size and ball velocity.
 * Use arrow keys to increase/decrease the values.
 */
class OptionsMenu: public MenuBase {
public:
	OptionsMenu(sf::RenderWindow& window);
	const Options& getOptions() const;
	int handleKey(sf::Event event) override;

private:
	Options m_options;
};