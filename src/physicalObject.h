#pragma once

#include "observer.h"
/** @cond */
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
/** @endcond */

class Observer;

/** @brief PhysicalObject class
 *
 * PhysicalObject is the base class for all objects that can be moved in the game. It holds a shape and is able to notify observers.
 * The move() function is used for physics-based movement of the object (in contrast to movement based on game logic, which uses the setDestination() function), 
 * and implementations of this function are expected to be in derived classes.
 * 
 * \note The class is not abstract yet, because only two classes derive from it (Paddle and Ball); and Paddle does not use a move() function yet.
 */
class PhysicalObject {
	friend class upCommand;
	friend class downCommand;

	public:
	explicit PhysicalObject(std::unique_ptr<sf::Shape> shape);
	~PhysicalObject();
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);
	bool doesCollide(const sf::Shape& other) const;
	bool doesCollide(const PhysicalObject& other) const;
	const sf::Shape& getShape() const;
	//virtual void move() = 0; //to do

	protected:
	void move(const sf::Vector2f& destination); //to rename to setDestination
	std::unique_ptr<sf::Shape> m_shape;
	
	private:
	std::vector<Observer*> m_observers;

	void notifyCollision() const;
};