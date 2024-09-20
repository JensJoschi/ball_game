#ifndef MOUSE_H
#define MOUSE_H

#include "controller.h"
#include "command.h"
/** @cond */
#include <SFML/Graphics.hpp>
#include <vector>
/** @endcond */

class PlayerMouse : public Controller{
    public:
    PlayerMouse(float sensitivity, const sf::Window& window); 
    PlayerMouse() = delete;
    Command* action(const std::vector<sf::Event>& events) override;

    private:
    sf::Vector2i m_previousMouse;
    const sf::Window& m_win;
};

#endif // MOUSE_H