#include "menu.h"
#include "game.h"
#include "inputSettings.h"
#include "optionMenu.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>
#include <memory>
#include <cassert>

int main() {

    float width = 800.0;
    float height = 600.0;
    sf::RenderWindow window(sf::VideoMode(width, height), "Ball game");
    window.setFramerateLimit(60);
    const std::string f = "arial.ttf";
    Menu m{ window, f };
    m.run();
    InputSettings p1{ std::move(*m.getP1()) };
    InputSettings p2{ std::move(*m.getP2()) };
    Game game(
           m.getOptions(), 
           std::move(p1),
		   std::move(p2),
                        window);
    game.run();
    std::cout << "game over.";
}