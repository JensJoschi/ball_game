#include "playermouse.h"
#include "command.h"
/** @cond */
#include <SFML/Graphics.hpp>
#include <vector>
#include <cassert>
/** @endcond */

PlayerMouse::PlayerMouse(const PlayerMouseParams* opt)
: Controller(opt), m_params(opt), m_previousMouse() {}


Command* PlayerMouse::action(const std::vector<sf::Event>& events){
    assert (up != nullptr && down != nullptr);
    if (events.empty()) return nullptr;
    for (const auto& event : events){
        if (event.type == sf::Event::MouseMoved) {
            if (event.mouseMove.y < m_previousMouse.y) {
                m_previousMouse = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
                return up.get();
            } else if (event.mouseMove.y > m_previousMouse.y) {
                m_previousMouse = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
                return down.get();
            }
        }
        else if (event.type == sf::Event::MouseLeft) {
            sf::Mouse::setPosition(m_previousMouse, m_params->m_win);
        }
    }
    return nullptr;
}