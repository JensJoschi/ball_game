#pragma once
#include "observer.h"
/** @cond */
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <vector>
/** @endcond */

enum class items{
    P1, P2, BALL, SCORE1, SCORE2
};

class GameState: public Observer{
    public: 
    GameState();
    void addDrawable(items i, const sf::Drawable* newD);
    virtual void onNotify(const sf::Drawable* oldD, const sf::Drawable* newD) override;
    virtual void onDangle(const sf::Drawable* selfSubject) override;
    std::vector<const sf::Drawable*> drawables;
};

