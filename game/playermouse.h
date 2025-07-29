#pragma once

#include "controller.h"
#include "command.h"
/** @cond */
#include <SFML/Graphics.hpp>
#include <vector>
/** @endcond */

class PlayerMouse : public Controller{
    public:
        PlayerMouse(ControllerSettings general, PlayerMouseParams specific, sf::RenderWindow& window);
    PlayerMouse() = delete;
    Command* action(const std::vector<sf::Event>& events) override;

    private:
	sf::RenderWindow* m_window;
    const PlayerMouseParams m_params;
    sf::Vector2i m_previousMouse;
};