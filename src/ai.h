#pragma once

#include "controller.h"
#include "command.h"
#include "gameState.h"
/** @cond */
#include <SFML/Graphics.hpp>
#include <vector>
/** @endcond */

struct AISetupParams : ControllerSettings {
	const GameState* state;
	items m_own;
};

class AI : public Controller{
    public:
    AI(const AISetupParams* opt); 
    AI() = delete;
    Command* action(const std::vector<sf::Event>& events) override;

    private:
	const AISetupParams* m_params;
};