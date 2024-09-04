#ifndef PADDLE_H
#define PADDLE_H

#include "physicalObject.h"
#include <cassert>
#include <memory>

/*! 
    *  \brief Paddle class
    *  \details
    *  The Paddle is used to defend one side of the playfield. It can be moved up and down.
    * \note Very simple class, no need to add cpp file yet
    */
class Paddle: public PhysicalObject {
    public:
    Paddle(sf::Vector2f pos, float height, float width) 
    : PhysicalObject(std::make_unique<sf::RectangleShape>(sf::Vector2f(width, height))) {
        m_shape->setPosition(pos.x, pos.y);
    }
    void changeSize(double size) {
        assert(size > 0);
    }
    ~Paddle() = default;
};

#endif // PADDLE_H