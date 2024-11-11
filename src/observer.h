#pragma once

/** @cond */
#include <SFML/Graphics.hpp>
/** @endcond */

enum class obsEvents { collision, score, none };

class Observer {
public:
    Observer(){}
    virtual void onNotify(const sf::Drawable* selfSubject, obsEvents event) = 0;
    virtual void onDangle(const sf::Drawable* selfSubject) = 0;
};
