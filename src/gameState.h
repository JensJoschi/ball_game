#pragma once
#include "observer.h"
/** @cond */
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <vector>
/** @endcond */

class GameState: public Observer{
    friend class Renderer;
    public: 
    GameState() = default;
    void addDrawable(const sf::Drawable* object);
    virtual void onNotify(const sf::Drawable* oldD, const sf::Drawable* newD) override;
    virtual void onDangle(const sf::Drawable*) override;
    protected:
    std::vector<const sf::Drawable*> drawables;
};

