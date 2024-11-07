#pragma once

/** @cond */
#include <SFML/Graphics.hpp>
/** @endcond */

enum class events { collision, none };

class Observer {
public:
    Observer(){}
    virtual void onNotify(const sf::Drawable* selfSubject, events event) = 0;
    virtual void onDangle(const sf::Drawable* selfSubject) = 0;
};
