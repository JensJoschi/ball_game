#include "ai.h"
#include "controller.h"
#include "inputsettings.h"
#include "command.h"
#include "gameState.h"
#include "enums.h"
/** @cond */
#include <SFML/Graphics.hpp>
#include <cassert>
/** @endcond */

AI::AI(ControllerSettings general, AISetupParams specific)
: Controller(std::move(general)), params(std::move(specific)), state(nullptr) {
	assert(params.m_own == items::P1 || params.m_own == items::P2);
}

Command* AI::action(const std::vector<sf::Event>& events){
	assert(state);
    auto ball = dynamic_cast<const sf::Transformable*>(state->drawables[(static_cast<int>(items::BALL))]);
    auto ownID = dynamic_cast<const sf::Transformable*>(state->drawables[static_cast<int>(params.m_own)]);

    assert (ball && ownID);

    if (ball->getPosition().y < ownID->getPosition().y) {
        return up.get();
    } else {
        return down.get();
    }
}

void AI::connect(const GameState* state) {
    assert(state);
	this->state = state;
}