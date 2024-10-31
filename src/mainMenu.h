#pragma once
#include "menuBase.h"
#include "enums.h"
/** @cond */
#include <sfml/Graphics.hpp>
#include <vector>
#include <string>
/** @endcond */


class MainMenu : public MenuBase {
public:
    MainMenu(sf::RenderWindow& window);
    int handleKey(sf::Event event) override;
    Controls getP1() const;
    Controls getP2() const;

private:
    Controls m_p1;
    Controls m_p2;
    std::string castEnumToString(Controls c);
};