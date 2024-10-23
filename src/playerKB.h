#pragma once

#include "controller.h"
#include "command.h"
/** @cond */
#include <SFML/Graphics.hpp>
#include <vector>
/** @endcond */

struct PlayerKBSetupParams: ControllerSettings {
    sf::Keyboard::Key m_upKey;
    sf::Keyboard::Key m_downKey;
};

class PlayerKB : public Controller{
    public:
    PlayerKB(const PlayerKBSetupParams* opt);
    PlayerKB() = delete;
    Command* action(const std::vector<sf::Event>& events) override;

    private:
    const PlayerKBSetupParams* m_params;
};