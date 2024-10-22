#include "game.h"
#include "options.h"
#include "menu.h"
#include "controller.h"
#include "playerKB.h"
#include "playermouse.h"
#include "ai.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>
#include <memory>
#include <cassert>

enum Windows {MAIN_MENU, GAME, OPTIONS, KEYBINDINGS};

//to move into game
Controller* createController(Controls control, sf::RenderWindow& window){
    //todo: integrate keybindings
    PlayerKBSetupParams p{ 250.0, sf::Keyboard::W, sf::Keyboard::S };
    switch (control){
        case Controls::KB:
            return new PlayerKB(p);
        case Controls::MOUSE:
            return new PlayerMouse(250.0, window);
        case Controls::AI:
            // return new AI();
			assert(false && "AI not implemented");
			return nullptr;
        default:
            return nullptr;
    }
}

int main(){
    float width= 800.0;
    float height= 600.0;
    sf::RenderWindow window(sf::VideoMode(width, height), "Ball game");
    window.setFramerateLimit(60);

    Menu mainMenu(window);
    std::unique_ptr<Game> game = nullptr;
    Options opt;
    sf::Clock clock;
    Windows currentState{ Windows::MAIN_MENU };

    while (window.isOpen()) {
        sf::Time elapsed = clock.restart(); 
        std::vector<sf::Event> events;
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();}
            events.push_back(event);
        }
        window.clear();
        bool keysOfP1 = true;

        switch (currentState){
            case MAIN_MENU:
                switch (mainMenu.update(events)){
                    case MenuState::P1:
                        currentState = KEYBINDINGS;
                        keysOfP1 = true;
                        break;
                    case MenuState::P2:
                        currentState = KEYBINDINGS;
                        keysOfP1 = false;
                        break;
                    case MenuState::OPTIONS:
                        currentState = OPTIONS;
                        break;
                    case MenuState::START:
                        game = std::make_unique<Game>(opt, createController(mainMenu.getP1(), window), createController(mainMenu.getP2(), window), window);
                        currentState = GAME;
                }
                break;
            case GAME:
                assert(game);
                if (game->update(events, elapsed)) {
                    currentState = MAIN_MENU;
                    game.reset();
                }
                break;
            case OPTIONS:
                //temporary, no error checking at all because will be replaced anyway
				std::cout << "Please enter Size of player 1: "; 
				std::cin >> opt.player1Size;
				std::cout << "Please enter Size of player 2: ";
				std::cin >> opt.player2Size;
				std::cout << "Please enter Ball velocity: ";
				std::cin >> opt.ballVelocity;
                currentState = MAIN_MENU;
                break;
            case KEYBINDINGS:
            //menu.changeKB(keysOfP1, keybindings->update(keysOfP1));
                currentState = MAIN_MENU;
                break;
            default:
                break;
        }
    }
    return 0;
}