#pragma once
#include "gameState.h"
/** @cond */
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <vector>
/** @endcond */


/** @brief Class for rendering the game state
 *
 * This class is responsible for rendering the game state. Game state is a central registry containing the current state of the game. The renderer uses this information to draw the game on the screen.
 */
class Renderer{
    public: 
    Renderer(sf::RenderWindow* window, const GameState& gs): window(window), m_gameState(gs){};
    void display();
    int getNoObjects();
    private:
    sf::RenderWindow* window;
    const GameState& m_gameState;
};

