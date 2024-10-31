#include "gameState.h"
#include "enums.h"
/** @cond */
#include <cassert>
#include <algorithm>
/** @endcond */

GameState::GameState(){
	drawables.resize(5);
}

void GameState::onNotify(const sf::Drawable* oldD, const sf::Drawable* newD){
	assert(newD);
	auto it = std::find(drawables.begin(), drawables.end(), oldD);
	assert (it != drawables.end());
	*it = newD;
}

void GameState::onDangle(const sf::Drawable* selfSubject){
	assert(selfSubject);
	auto it = std::find(drawables.begin(), drawables.end(), selfSubject);
	assert (it != drawables.end());
	*it = nullptr;
}

void GameState::addDrawable(items i,  const sf::Drawable* object){
	assert(object);
	drawables[static_cast<int>(i)] = object;
}