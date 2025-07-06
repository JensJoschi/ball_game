#pragma once
#include "observer.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Sound : public Observer {
public:
	Sound() {};
	~Sound() {};
	virtual void onNotify(const sf::Drawable* selfSubject, obsEvents e) override {
		if (e == obsEvents::collision) {
			std::cout << "Beep!";
		}
		else if (e == obsEvents::score) {
			std::cout << "ding!";
		}
	}
	virtual void onDangle(const sf::Drawable* selfSubject) override { std::cout << "Pling!"; }
};