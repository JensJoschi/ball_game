#pragma once

#include "physicalObject.h"
/** @cond */
#include <cassert>
#include <memory>
/** @endcond */

/*! 
    *  \brief Paddle class
    *  \details
    *  The Paddle is used to defend one side of the playfield.
	* It does not move on its own by any physics, but can be moved by Commands (which are friends of PhysicalObjects)
    * \note Very simple class, no need to add cpp file yet
    */
class Paddle: public PhysicalObject {
    public:
    Paddle(sf::Vector2f pos, float height, float width) 
    : PhysicalObject(std::make_unique<sf::RectangleShape>(sf::Vector2f(width, height))) {
        m_shape->setPosition(pos.x, pos.y);
    }
	explicit Paddle(std::unique_ptr<sf::Shape> shape) : PhysicalObject(std::move(shape)) {}
	void move(sf::Time elapsed) override {}; //no inertia, no acceleration or other physics here. 
    void changeSize(float factor) {
        assert(factor > 0);
        sf::Vector2f currsize = static_cast<sf::RectangleShape*>(m_shape.get())->getSize();
		static_cast<sf::RectangleShape*>(m_shape.get())->setSize(currsize * factor);
    }
    ~Paddle() = default;
};
