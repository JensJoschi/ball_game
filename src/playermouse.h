#pragma once

#include "controller.h"
#include "command.h"
/** @cond */
#include <SFML/Graphics.hpp>
#include <vector>
/** @endcond */


struct PlayerMouseParams : ControllerSettings {
    const sf::Window& m_win;
};


class PlayerMouse : public Controller{
    public:
    PlayerMouse(const PlayerMouseParams* opt); 
    PlayerMouse() = delete;
    Command* action(const std::vector<sf::Event>& events) override;

    private:
    const PlayerMouseParams* m_params;
    sf::Vector2i m_previousMouse;
};