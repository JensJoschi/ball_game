#pragma once

#include "controller.h"
#include "command.h"
/** @cond */
#include <SFML/Graphics.hpp>
#include <vector>
/** @endcond */

class PlayerKB : public Controller{
    public:
    PlayerKB(ControllerSettings general, PlayerKBSetupParams specific);
    PlayerKB() = delete;
    Command* action(const std::vector<sf::Event>& events) override;

    private:
     PlayerKBSetupParams m_params;
};