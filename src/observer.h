#pragma once

/** @cond */
#include <SFML/Graphics.hpp>
/** @endcond */

class Observer {
public:
    Observer(){}
    virtual void onNotify(const sf::Drawable* oldD, const sf::Drawable* newD) = 0;
    virtual void onDangle(const sf::Drawable* selfSubject) = 0;
};
