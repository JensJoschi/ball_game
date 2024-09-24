#include "ai.h"

AI::AI(int difficulty, const GameState& gs, items own): Controller(static_cast<double> (difficulty * 100)), state(gs), own(own) {
    assert(difficulty > 0);
}

Command* AI::action(const std::vector<sf::Event>& events){
    auto ball = dynamic_cast<const sf::Transformable*>(state.drawables[static_cast<int>(items::BALL)]);
    auto ownID = dynamic_cast<const sf::Transformable*>(state.drawables[static_cast<int>(own)]);

    assert (ball && ownID);

    if (ball->getPosition().y < ownID->getPosition().y) {
        return up.get();
    } else {
        return down.get();
    }
}