#ifndef PHYSICALOBJECT_H
#define PHYSICALOBJECT_H

#include "observer.h"
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class Observer;

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

	protected:
	void move(const sf::Vector2f& destination);
	std::unique_ptr<sf::Shape> m_shape;
	
	private:
	std::vector<Observer*> m_observers;
	/**
	 * \brief notify change of position
	 * \details
	 * reports to all observers that the position has changed. This allows graphics etc to update state
	 */
	void notifyPositionChange() const;
};

#endif // PHYSICALOBJECT_H