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

enum Windows {MAIN_MENU, GAME, OPTIONS, KEYBINDINGS};

Controller* createController(Controls control, sf::RenderWindow& window){
    //todo: integrate options, keybindings
    switch (control){
        case Controls::KB:
            PlayerKBSetupParams p{250.0, sf::Keyboard::W, sf::Keyboard::S};
            return new PlayerKB(p);
        case Controls::MOUSE:
            return new PlayerMouse(250.0, window);
        case Controls::AI:
            // return new AI();
        default:
            return nullptr;
    }
}

int main(){
    float width= 800.0;
    float height= 600.0;
    sf::RenderWindow window(sf::VideoMode(width, height), "Ball game");
    Windows currentState {Windows::MAIN_MENU};
    Menu mainMenu(window);
    std::unique_ptr<Game> game = nullptr;
    window.setFramerateLimit(60);
    sf::Clock clock;
    Controller* p1 = nullptr;
    Controller* p2 = nullptr;

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
                        p1 = createController(mainMenu.getP1(), window);
                        p2 = createController(mainMenu.getP2(), window);
                        assert(p1);
                        assert(p2);
                        Options o; //to do
                        game = std::make_unique<Game>(o, p1, p2, window); 
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
            //...
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