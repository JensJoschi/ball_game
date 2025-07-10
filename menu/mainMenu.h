#pragma once
#include "menuBase.h"
#include "enums.h"
/** @cond */
#include <sfml/Graphics.hpp>
#include <vector>
#include <string>
/** @endcond */

/*!
	*  \brief MainMenu class
	*  \details
	*  This class lets the user choose the control scheme for the players, go into options, or start the game.

	*/
class MainMenu : public MenuBase {
public:
    MainMenu(sf::RenderWindow& window, const std::string& fontpath);
	/** @brief Handle keys
	* cursors are used to move up/down in menu and to switch between control schemes for player 1 and 2.
	* Enter is used to select an option. Return value is 0 for staying in main menu, 1 keyboard submenu, 2 for mouse submenu, 3 for AI submenu, 4 for options, 5 for starting the game.
	**/
    Windows handleKey(sf::Event event) override; 
	bool isOnP1() const;
	Controls getP1() const;
	Controls getP2() const;

private:
	bool onP1;
	Controls m_p1;
	Controls m_p2;
    std::string castEnumToString(Controls c);
};