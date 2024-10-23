#include "playerKB.h"
#include "command.h"

/** @cond */
#include <iostream>
#include <cassert>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
/** @endcond */

PlayerKB::PlayerKB(const PlayerKBSetupParams* opt) 
    : Controller(opt), m_params(opt) {
    assert(opt);
}

Command* PlayerKB::action(const std::vector<sf::Event>& events){
    assert (up != nullptr && down != nullptr);
    if (events.empty()) return nullptr;
    for (const auto& event : events){
        if (event.type == sf::Event::KeyPressed && event.key.code == m_params->m_upKey) return (up.get());
        else if (event.type == sf::Event::KeyPressed && event.key.code == m_params->m_downKey) return (down.get());
    }
    return nullptr;
}