#ifndef PLAYER_H
#define PLAYER_H

#include "controller.h"
#include "command.h"
/** @cond */
#include <SFML/Graphics.hpp>
#include <vector>
/** @endcond */

struct PlayerKBSetupParams{
    double m_sensitivity;
    sf::Keyboard::Key m_upKey;
    sf::Keyboard::Key m_downKey;
};

class PlayerKB : public Controller{
    public:
    PlayerKB(const PlayerKBSetupParams& params); 
    PlayerKB() = delete;
    Command* action(const std::vector<sf::Event>& events) override;

    private:
    PlayerKBSetupParams m_params;
};

#endif // PLAYER_H