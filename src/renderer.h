#pragma once
#include "physicalObject.h"

/** @cond */
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <vector>
/** @endcond */

class Renderer{ //inherit from observer?
    public: 
    Renderer(sf::RenderWindow* window): window(window){};
    void display();
    void addDrawable(const sf::Drawable* object);
    private:
    sf::RenderWindow* window;
    std::vector<const sf::Drawable*> drawables;
};

