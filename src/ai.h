#pragma once

#include "controller.h"
#include "command.h"
#include "gameState.h"
/** @cond */
#include <SFML/Graphics.hpp>
#include <vector>
/** @endcond */

class AI : public Controller{
    public:
    AI(int difficulty, const GameState& state, items own); 
    AI() = delete;
    Command* action(const std::vector<sf::Event>& events) override;

    private:
    const GameState& state;
    items own;
};