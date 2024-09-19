#include "renderer.h"

/** @cond */
#include <cassert>
#include <algorithm>
#include <iostream>
/** @endcond */

void Renderer::display(){
	window->clear(sf::Color::Black);
	for (const auto& obj : drawables){
        if (obj){ 
            window->draw(*obj); 
        } 
    }
	window->display();
}

void Renderer::addDrawable( const sf::Drawable* object){
	assert(object);
	drawables.emplace_back(object);
}

