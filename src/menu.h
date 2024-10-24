#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "options.h"

enum class MenuState{
    P1    = 0,
    P2    = 1, 
    OPTIONS = 2,
    START = 3,
    COUNT = 4,
    NONE = 5
    };

enum class Controls{
    KB    = 0, 
    MOUSE = 1,
    AI    = 2,
    COUNT = 3
};

class Menu{
    public:
    Menu(sf::RenderWindow& window);
    MenuState update(const std::vector<sf::Event>& events);
    Controls getP1() const;
    Controls getP2() const;
    
    private:
    void display();
	void drawMenuStateText();

    template <typename Enum>
    static Enum incrementEnum(Enum value, Enum count) {
        return static_cast<Enum>((static_cast<int>(value) + 1) % static_cast<int>(count));
    }
    template <typename Enum>
    static Enum decrementEnum(Enum value, Enum count) {
        return static_cast<Enum>((static_cast<int>(value) - 1 + static_cast<int>(count)) % static_cast<int>(count));
    }

	std::string castEnumToString(Controls c);
	std::string castEnumToString(MenuState c);

    Controls m_p1;
    Controls m_p2;
    MenuState highlighted;
    sf::RenderWindow& m_window;
    sf::Font m_font;
    std::vector<sf::Text> m_menuTexts;
};
// void Game::assignControls(){
//     std::cout << "Player 1, please enter up key" << std::endl;
//     sf::Keyboard::Key upKey = getKeyPressed();
//     std::cout << "Player 1, please enter down key" << std::endl;
//     sf::Keyboard::Key downKey = getKeyPressed();
//     PlayerKBSetupParams p1Params{250.0, upKey , downKey};
//     m_c1 = std::make_unique<PlayerKB>(p1Params);

//     // std::cout << "Player 2, please enter up key" << std::endl;
//     // upKey = getKeyPressed();
//     // std::cout << "Player 2, please enter down key" << std::endl;
//     // downKey = getKeyPressed();
//     // PlayerKBSetupParams p2Params{250.0, upKey , downKey};
//     // m_c2 = std::make_unique<PlayerKB>(p2Params);

//     // m_c2 = std::make_unique<PlayerMouse>(250.0, m_window);
//     m_c2 = std::make_unique<AI>(1, m_gameState, items::P2);

// }

// sf::Keyboard::Key Game::getKeyPressed(){
//     while (true){
//         sf::Event event;
//         while (m_window.pollEvent(event)) {
//             if (event.type == sf::Event::KeyPressed) {
//                 return event.key.code;
//             }
//         }
//     }
// }