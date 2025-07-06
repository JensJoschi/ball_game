#pragma once
#include "menuBase.h"
#include "options.h"
/** @cond */
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
/** @endcond */

/** @brief OptionsMenu class
 *
 * allows the player to change the game settings such as paddle size and ball velocity.
 * Use arrow keys to increase/decrease the values.
 */
class OptionsMenu: public MenuBase {
public:
	OptionsMenu(sf::RenderWindow& window);
	const Options& getOptions() const;
	Windows handleKey(sf::Event event) override;

private:
	Options m_options;
};