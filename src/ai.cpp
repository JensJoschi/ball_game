#include "ai.h"
#include "controller.h"
#include "gameState.h"
#include "enums.h"
#include "command.h"
/** @cond */
#include <cassert>
#include <SFML/Graphics.hpp>
/** @endcond */

AI::AI(const ControllerSettings general, const AISetupParams specific) : Controller(general),
m_params(specific), state(nullptr) {

	assert(m_params.m_own == items::P1 || m_params.m_own == items::P2);

}

Command* AI::action(const std::vector<sf::Event>& events){
	assert(state);
    auto ball = dynamic_cast<const sf::Transformable*>(state->drawables[(static_cast<int>(items::BALL))]);
    auto ownID = dynamic_cast<const sf::Transformable*>(state->drawables[static_cast<int>(m_params.m_own)]);

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