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
 * Diffent concrete PhysicalObjects differ in the physics / game logic of movement, hence the pure virtual move() function.
 * 
 */
class PhysicalObject {
	friend class upCommand;
	friend class downCommand;

	public:
	explicit PhysicalObject(std::unique_ptr<sf::Shape> shape);
	virtual ~PhysicalObject();
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);
	bool doesCollide(const sf::Shape& other) const;
	bool doesCollide(const PhysicalObject& other) const;
	const sf::Shape& getShape() const;
	virtual void move(sf::Time elapsed) = 0;

	protected:
	void setDestination(const sf::Vector2f& destination);
	std::unique_ptr<sf::Shape> m_shape;
	
	private:
	std::vector<Observer*> m_observers;
	void notifyCollision() const;
};