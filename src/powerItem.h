#pragma once
#include "observer.h"
#include "physicalObject.h"
/** @cond */
#include <SFML/Graphics.hpp>
/** @endcond */


enum class ItemType {
	Shrink,
	Enlarge,
	SpeedUp,
	SlowDown,
	ChangeColor,
	Bounce
};


class PowerItemBASE : public PhysicalObject {
public:
	PowerItemBASE(sf::Vector2f pos) : PhysicalObject(std::make_unique<sf::CircleShape>(30)) {
		m_shape->setPosition(pos.x, pos.y);
	}
	PowerItemBASE() = default;
	virtual ~PowerItemBASE() = default;

	void move(sf::Time elapsed) override {} //no movement
	void vanish(){
		for (const auto& observer : m_observers) {
			observer->onNotify(this->m_shape.get(), Effects::explosion);
			observer->onNotify(this->m_shape.get(), call());
		}
	}
	virtual ItemType getType() = 0;
	virtual SpecEvents call() = 0;
private:
};

template <ItemType T>
class PowerItem : public PowerItemBASE {
public:
	PowerItem(sf::Vector2f pos) : PowerItemBASE(pos) {
		switch (T) {
		case ItemType::Shrink:
			m_shape->setFillColor(sf::Color::Red);
			break;
		case ItemType::Enlarge:
			m_shape->setFillColor(sf::Color::Green);
			break;
		case ItemType::SpeedUp:
			m_shape->setFillColor(sf::Color::Blue);
			break;
		case ItemType::SlowDown:
			m_shape->setFillColor(sf::Color::Yellow);
			break;
		case ItemType::ChangeColor:
			m_shape->setFillColor(sf::Color::Magenta);
			break;
		case ItemType::Bounce:
			m_shape->setFillColor(sf::Color::White);
			break;

		}
	}
	ItemType getType() override {
		return T;
	}
	SpecEvents call() override {
		switch (T) {
		case ItemType::Shrink:
			return SpecEvents::shrink;
		case ItemType::Enlarge:
			return SpecEvents::expand;
		case ItemType::SpeedUp:
			return SpecEvents::speedup;
		case ItemType::SlowDown:
			return SpecEvents::slow;
		case ItemType::ChangeColor:
			return::SpecEvents::colorChange;
		case ItemType::Bounce:
			return SpecEvents::bounce;
		}
	}
	~PowerItem() override = default;
};