#pragma once
#include "observer.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <variant>

class Sound : public Observer {
public:
	Sound() {};
	~Sound() {};
	virtual void onNotify(const sf::Drawable* selfSubject, std::variant<ObsEvents, Effects, SpecEvents> e) override {
		if (std::holds_alternative<Effects>(e)) {
			if (std::get<Effects>(e) == Effects::collision) {
				std::cout << "Beep!";
			}
			else if (std::get<Effects>(e) == Effects::score) {
				std::cout << "ding!";
			}
			else if (std::get<Effects>(e) == Effects::explosion) {
				std::cout << "Skadoosh!";
			}
		}
	}
	virtual void onDangle(const sf::Drawable* selfSubject) override { std::cout << "Pling!"; }
};