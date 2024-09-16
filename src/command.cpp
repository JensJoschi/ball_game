#include "command.h"
#include "physicalObject.h"

/** @cond */
#include <cassert>
#include <SFML/Graphics.hpp>
/** @endcond */

Command::Command(double moveBy): m_moveBy(moveBy){
    assert(m_moveBy > 0);
}

void upCommand::execute(PhysicalObject& object, const sf::Time& elapsed){
    sf::Vector2f p = object.m_shape.get()->getPosition();
    p.y -= m_moveBy * elapsed.asSeconds();
    object.move(p);
//could also access and modify object.m_center directly but this would not trigger
//the desired side effects (e.g. observers)
}

void downCommand::execute(PhysicalObject& object, const sf::Time& elapsed){
    sf::Vector2f p = object.m_shape.get()->getPosition();
    p.y += m_moveBy * elapsed.asSeconds();
    object.move(p);
}

