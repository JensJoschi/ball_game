#include "game.h"
#include "options.h"
#include "mainMenu.h"
#include "controller.h"
#include "playerKB.h"
#include "playermouse.h"
#include "ai.h"
#include "inputSettings.h"
#include "enums.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>
#include <memory>
#include <cassert>

enum Windows {MAIN_MENU, GAME, OPTIONS, INPUTSETTINGS};

int main(){
    float width= 800.0;
    float height= 600.0;
    sf::RenderWindow window(sf::VideoMode(width, height), "Ball game");
    window.setFramerateLimit(60);

    MainMenu mainMenu(window);
    std::unique_ptr<Game> game = nullptr;
    std::unique_ptr<OptionsMenu> optionsMenu{ std::make_unique<OptionsMenu>(window) };
	std::unique_ptr<InputSettings> inputSettings{ std::make_unique<InputSettings>(window) };
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
        bool changingP1 = true;

        switch (currentState){
            case MAIN_MENU:
                switch (mainMenu.update(events)){
                case 0:
					currentState = MAIN_MENU;
					break;
                case 1:
                    currentState = INPUTSETTINGS;
                    changingP1 = true;
					//inputSettings.setPlayer(true, mainMenu.getP1());
                    break;
                case 2:
                    currentState = INPUTSETTINGS;
                    changingP1 = false;
                    //inputSettings.setPlayer(false,  mainMenu.getP2());
                    break;
                case 3:
                    currentState = OPTIONS;
                    break;
                case 4:
                    game = std::make_unique<Game>(
                        optionsMenu->getOptions(), 
                        std::move(inputSettings->getControllerSettings(mainMenu.getP1(), true)),
						std::move(inputSettings->getControllerSettings(mainMenu.getP2(), false)),
                        window);
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
				if (optionsMenu->update(events)) {
				currentState = MAIN_MENU;
                }
                break;
            case INPUTSETTINGS:
                //if (inputSettings->update(events) {
                    currentState = MAIN_MENU;
                //}
                break;
            default:
                break;
        }
    }
    return 0;
}