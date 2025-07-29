#pragma once


/** @cond */
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
/** @endcond */

/** @brief Base class for menus
 *
 * This class is the base
 * class for all menus in the game. It contains the basic functionality for displaying and navigating through menus.
 * Usage: construct with a vector of strings, where each string is an item in the menu. Arrow keys can be used to cycle through those items.
 */
class MenuBase {
public:
    MenuBase(sf::RenderWindow& window, const std::vector<std::string>& items);
	virtual ~MenuBase() = default; //window is not owned by the menu
	int update(const std::vector<sf::Event>& events);
	void display();
	void highlight();
	virtual int handleKey(sf::Event event) = 0;

protected:
    template <typename Enum>
	static Enum incrementEnum(Enum value, Enum count) { //allows cycling through modes of an item, e.g. difficulty levels or control types. Not used by all derived Menus.
        return static_cast<Enum>((static_cast<int>(value) + 1) % static_cast<int>(count));
    }
    template <typename Enum>
    static Enum decrementEnum(Enum value, Enum count) {
        return static_cast<Enum>((static_cast<int>(value) - 1 + static_cast<int>(count)) % static_cast<int>(count));
    }
    int highlighted;
    sf::RenderWindow& m_window;
    std::vector<sf::Text> m_menuTexts;

private:
    sf::Font m_font;
};
