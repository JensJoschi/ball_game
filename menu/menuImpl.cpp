#include <SFML/Graphics.hpp>
#include "menuImpl.h"
#include "inputSettings.h"
#include "mainMenu.h"
#include "optionMenu.h"

MenuImpl::MenuImpl(sf::RenderWindow& w, const std::string& fontpath) : window(w),
optionsMenu(std::make_unique<OptionsMenu>(w, fontpath)),
mainMenu(std::make_unique<MainMenu>(w, fontpath)) {
}

void MenuImpl::run() {
    Windows currentState{ Windows::MAIN_MENU };

    while (window.isOpen()) {
        std::vector<sf::Event> events;
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            events.push_back(event);
        }
        window.clear();

        switch (currentState) {
        case MAIN_MENU:
            currentState = mainMenu->update(events);
            break;
        case OPTIONS:
            currentState = optionsMenu->update(events);
            break;
        case KEYBOARD:
            currentState = Windows::MAIN_MENU; //keyboardMenu to write
            break;
            //mouse, AI have no menu yet

        case START:
            if (!P1Inputs) {
                P1Inputs = createStandardInput(mainMenu->getP1(), items::P1);
            }
            if (!P2Inputs) {
                P2Inputs = createStandardInput(mainMenu->getP2(), items::P2);
            }
            return;
            //startGame with auto p1 = getP1(), auto p2 = getP2(), auto opt = getOptions(), window


        default:
            currentState = MAIN_MENU;
            break;
        }
    }
}

std::unique_ptr<InputSettings> MenuImpl::createStandardInput(Controls c, items  i) {
    switch (c) {
    case Controls::KB:
        return std::make_unique<InputSettings>(ControllerSettings{ 200.0 }, PlayerKBSetupParams(sf::Keyboard::Key::W, sf::Keyboard::Key::S));
    case Controls::MOUSE:
        return std::make_unique<InputSettings>(ControllerSettings{ 200.0 }, PlayerMouseParams());
    case Controls::AI:
        return std::make_unique<InputSettings>(ControllerSettings{ 200.0 }, AISetupParams(i));
    default:
        return nullptr;
    }
}

const Options& MenuImpl::getOptions() const {
    return optionsMenu->getOptions();
}

std::unique_ptr<InputSettings> MenuImpl::getP1() {
    return std::move(P1Inputs);
}

std::unique_ptr<InputSettings> MenuImpl::getP2() {
    return std::move(P2Inputs);
}



