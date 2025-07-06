#pragma once

#include "controller.h"
#include "command.h"
/** @cond */
#include <SFML/Graphics.hpp>
#include <vector>
/** @endcond */

class PlayerKB : public Controller{
    public:
    PlayerKB(const ControllerSettings general, const PlayerKBSetupParams specific);
    PlayerKB() = delete;
    Command* action(const std::vector<sf::Event>& events) override;

    private:
    const PlayerKBSetupParams m_params;
};