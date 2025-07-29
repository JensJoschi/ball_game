#include "gameState.h"
#include "enums.h"
/** @cond */
#include <cassert>
#include <algorithm>
#include <variant>
/** @endcond */

GameState::GameState(): collisionCount(0){
	drawables.resize(6);
}

void GameState::exchangeDrawable(const sf::Drawable* oldD, const sf::Drawable* newD){
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

int GameState::getCollision() const {
	return collisionCount;
}

void GameState::onNotify(const sf::Drawable* selfSubject, std::variant<ObsEvents, Effects, SpecEvents> e) {
	if (std::holds_alternative<ObsEvents>(e)) {
		ObsEvents event = std::get<ObsEvents > (e);
		if (event == ObsEvents::collision) {
			collisionCount++;
		}
	}
	else if (std::holds_alternative<SpecEvents>(e)) {
		SpecEvents event = std::get<SpecEvents>(e);
		if (event != SpecEvents::none){
			specialEvent = event;
		}
	}
}

SpecEvents GameState::getSpecialEvent() {
	auto temp = specialEvent;
	specialEvent = SpecEvents::none;
	return temp;
}

void GameState::addDrawable(items i,  const sf::Drawable* object){
	assert(object);
	drawables[static_cast<int>(i)] = object;
}

bool GameState::isCollisionThresReached() {
	if ((collisionCount + 1) % 15 == 0) {
		if (act) { 
			act = false; 
			return true;
		}
		else { //disables subsequent calls until the next collision
			return false;
		}
	}
	else {
		act = true;
		return false;
	}
}