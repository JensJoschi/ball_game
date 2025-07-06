#include "game.h"
#include "menu.h"
#include "inputSettings.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>
#include <memory>
#include <cassert>

int main(){
    float width= 800.0;
    float height= 600.0;
    sf::RenderWindow window(sf::VideoMode(width, height), "Ball game");
    window.setFramerateLimit(60);
    Menu m{ window };
    Menu.run();
    std::unique_ptr<InputSettings> p1 = m.getP1();
    std::unique_ptr<InputSettings> p2 = m.getP2();
    Game game(
           m.getOptions(), 
           std::move(p1),
		   std::move(p2),
           window);
    game.run();
}