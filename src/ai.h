#pragma once

#include "controller.h"
#include "command.h"
#include "gameState.h"
#include "enums.h"
/** @cond */
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
/** @endcond */

struct AISetupParams{
	items m_own;
};

class AI : public Controller{
    public:
    AI(const ControllerSettings general, const AISetupParams specific);
    AI() = delete;
    Command* action(const std::vector<sf::Event>& events) override;
	void connect(const GameState* state);

    private:
   const AISetupParams m_params;
    const GameState* state;
};