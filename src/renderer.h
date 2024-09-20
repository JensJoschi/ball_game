#pragma once
#include "gameState.h"
/** @cond */
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <vector>
/** @endcond */

class Renderer{
    public: 
    Renderer(sf::RenderWindow* window, const GameState& gs): window(window), m_gameState(gs){};
    void display();
    int getNoObjects();
    private:
    sf::RenderWindow* window;
    const GameState& m_gameState;
};

