#include "physicalObject.h"
#include "observer.h"
#include <memory>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>


PhysicalObject::PhysicalObject(std::unique_ptr<sf::Shape> shape): m_shape(std::move(shape)) {
	m_shape->setFillColor(sf::Color::White);
}

PhysicalObject::~PhysicalObject() {
	for (auto i : m_observers) {
		// i->onDangle();
	}
}

void PhysicalObject::addObserver(Observer* observer) {
	m_observers.push_back(observer);
}

void PhysicalObject::removeObserver(Observer* observer) {
	m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
}

bool PhysicalObject::doesCollide(const sf::Shape& other) const {
	return m_shape->getGlobalBounds().intersects(other.getGlobalBounds());
}

bool PhysicalObject::doesCollide(const PhysicalObject& other) const {
	return m_shape->getGlobalBounds().intersects(other.getShape()->getGlobalBounds());
}

const sf::Shape* PhysicalObject::getShape() const {
	return m_shape.get();
}

void PhysicalObject::move(const sf::Vector2f& destination) {
    m_shape->setPosition(destination);
    notifyPositionChange();
}


void PhysicalObject::notifyPositionChange() const {
	//...
}