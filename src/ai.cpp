#include "ai.h"

AI::AI(const AISetupParams* opt): Controller(opt), m_params(opt) {
	assert(m_params->m_own == items::P1 || m_params->m_own == items::P2);
	assert(m_params->state);

}

Command* AI::action(const std::vector<sf::Event>& events){
    auto ball = dynamic_cast<const sf::Transformable*>(m_params->state->drawables[(static_cast<int>(items::BALL))]);
    auto ownID = dynamic_cast<const sf::Transformable*>(m_params->state->drawables[static_cast<int>(m_params->m_own)]);

    assert (ball && ownID);

    if (ball->getPosition().y < ownID->getPosition().y) {
        return up.get();
    } else {
        return down.get();
    }
}