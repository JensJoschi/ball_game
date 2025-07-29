#pragma once

#include "controller.h"
#include "command.h"
#include "gameState.h"
#include "enums.h"
/** @cond */
#include <SFML/Graphics.hpp>
#include <vector>
/** @endcond */

struct AISetupParams{
	items m_own;
};

/**
 * @brief AI class
 *
 * This class implements AI controlled movement. It moves up when below the ball, and down when above the ball.
 * To work it requires knowledge of its own ID (see struct AISetupParams) and the state of the game (Gamestate, though currently only to get the ball's position).
 * 
 */
class AI : public Controller{
    public:
    AI(const ControllerSettings general, const AISetupParams specific);
    AI() = delete;
	~AI() = default; //gameState is not owned by AI.
    Command* action(const std::vector<sf::Event>& events) override;
	void connect(const GameState* state);

    private:
    const AISetupParams m_params;
    const GameState* state;
};