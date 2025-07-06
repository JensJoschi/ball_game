
#include <SFML/Graphics.hpp>
#include "menu.h"
#include "inputSettings.h"
#include "mainMenu.h"
#include "optionMenu.h"

Menu::Menu(sf::RenderWindow& w) : window(w), 
    optionsMenu(std::make_unique<OptionsMenu> (w)), 
    mainMenu(std::make_unique<MainMenu>(w)){
}

void Menu::run() {
    sf::Clock clock;
    Windows currentState{ Windows::MAIN_MENU };

    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();
        std::vector<sf::Event> events;
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            events.push_back(event);
        }
        window.clear();

        std::unique_ptr<PlayerKBSetupParams> keyboardSettings;
        sf::Keyboard::Key up;
        sf::Keyboard::Key down;
        switch (currentState) {
        case MAIN_MENU:
            currentState = mainMenu->update(events);
            break;
        case OPTIONS:
            currentState = optionsMenu->update(events);
            break;
		case KEYBOARD:
//keyboardMenu to write
            up = sf::Keyboard::Key::W;
			down = sf::Keyboard::Key::S;
            keyboardSettings = std::make_unique<PlayerKBSetupParams>(200.0, up, down);
                currentState = MAIN_MENU;
                if (mainMenu->isOnP1()) {
                    P1Inputs = std::move(keyboardSettings);
				}
                else {
                    P2Inputs = std::move(keyboardSettings);
                }
			break;
        //mouse, AI to do

        case START:
            return;
			//startGame with auto p1 = getP1(), auto p2 = getP2(), auto opt = getOptions(), p1.getType(), p2.getType(), window


        default:
            currentState = MAIN_MENU;
            break;
        }
    }
}

const Options& Menu::getOptions() const {
    return optionsMenu->getOptions();
}

std::unique_ptr<InputSettings> Menu::getP1(){
	return std::move(P1Inputs);
}

std::unique_ptr<InputSettings> Menu::getP2(){
    return std::move(P2Inputs);
}



