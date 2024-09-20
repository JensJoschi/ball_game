#include "gameState.h"
/** @cond */
#include <cassert>
#include <algorithm>
/** @endcond */

void GameState::onNotify(const sf::Drawable* oldD, const sf::Drawable* newD){
	assert(oldD);
	onDangle(oldD);
	addDrawable(newD);
}

void GameState::onDangle(const sf::Drawable* object){
	assert(object);
    auto it = std::find(drawables.begin(), drawables.end(), object);
    if (it != drawables.end()) {
        *it = nullptr;
    }
}

void GameState::addDrawable( const sf::Drawable* object){
	assert(object);
	drawables.emplace_back(object);
}