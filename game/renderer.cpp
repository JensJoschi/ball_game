#include "renderer.h"

/** @cond */
#include <cassert>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
/** @endcond */

void Renderer::display(){
	sf::Color currentColor = m_gameState.getCollision() >= 5 ? sf::Color::Cyan : sf::Color::Black;
	window->clear(currentColor);
	for (const auto& obj : m_gameState.drawables){
        if (obj){ 
            window->draw(*obj); 
        } 
    }

	window->display();
}

int Renderer::getNoObjects(){
    return m_gameState.drawables.size();
}
