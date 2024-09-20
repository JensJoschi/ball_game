#include "renderer.h"

/** @cond */
#include <cassert>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
/** @endcond */

void Renderer::display(){
	window->clear(sf::Color::Black);
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
