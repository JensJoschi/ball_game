#include <SFML/Graphics.hpp>
#include <vector>
#include "options.h"

enum class MenuState{
    NONE  = 0,
    P1    = 1,
    P2    = 2, 
    OPTIONS = 3,
    START = 4,
    COUNT = 5,
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
    const Controls& getP1() const;
    const Controls& getP2() const;
    
    private:
    void display();
    template <typename Enum>
    static Enum incrementEnum(Enum value, Enum count) {
        return static_cast<Enum>((static_cast<int>(value) + 1) % static_cast<int>(count));
    }
    template <typename Enum>
    static Enum decrementEnum(Enum value, Enum count) {
        return static_cast<Enum>((static_cast<int>(value) - 1 + static_cast<int>(count)) % static_cast<int>(count));
    }

    Controls m_p1;
    Controls m_p2;
    MenuState highlighted;
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