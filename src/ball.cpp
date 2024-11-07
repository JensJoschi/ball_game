#include "ball.h"
/** @cond */
#include <cmath>
#include <cassert>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
/** @endcond */

Ball::Ball(sf::Vector2f pos, float size, double direction, double vel) 
: PhysicalObject(std::make_unique<sf::CircleShape>(size/2.0)),  
m_direction(direction), m_velocity(vel) {
    assert (direction >= 0 && direction <= 2 * M_PI);
    assert (vel > 0.0);
    m_shape->setPosition(pos.x, pos.y);
}

void Ball::move(sf::Time elapsed) {
    sf::Vector2f p = m_shape->getPosition();
    p.x += m_velocity * cos(m_direction) * elapsed.asSeconds();
    p.y += m_velocity * sin(m_direction) * elapsed.asSeconds();
    setDestination(p);
}

void Ball::rebounce(double surfaceAngle) {
    assert (surfaceAngle >= 0 && surfaceAngle <= 2 * M_PI);
    m_direction = 2 * surfaceAngle - m_direction;
    if (m_direction < 0) {
        m_direction += 2 * M_PI;
    } else if (m_direction >= 2 * M_PI) {
        m_direction -= 2 * M_PI;
    }
}