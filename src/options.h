#pragma once
#include "menuBase.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>


struct Options {
    float player1Size{ 50.0 };
    float player2Size{ 50.0 };
    int ballVelocity{ 50 };
};

class OptionsMenu: public MenuBase {
public:
	OptionsMenu(sf::RenderWindow& window);
	const Options& getOptions() const;
	int handleKey(sf::Event event) override;

private:
	Options m_options;
};