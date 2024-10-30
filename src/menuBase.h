#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class MenuBase {
public:
    MenuBase(sf::RenderWindow& window, const std::vector<std::string>& items);
    virtual ~MenuBase() = default;
	int update(const std::vector<sf::Event>& events);
	void display();
	void highlight();
	virtual int handleKey(sf::Event event) = 0;
protected:
    template <typename Enum>
    static Enum incrementEnum(Enum value, Enum count) {
        return static_cast<Enum>((static_cast<int>(value) + 1) % static_cast<int>(count));
    }
    template <typename Enum>
    static Enum decrementEnum(Enum value, Enum count) {
        return static_cast<Enum>((static_cast<int>(value) - 1 + static_cast<int>(count)) % static_cast<int>(count));
    }
    int highlighted;
    sf::RenderWindow& m_window;
    std::vector<sf::Text> m_menuTexts;

private:
    sf::Font m_font;
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