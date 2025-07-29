#pragma once

/** @cond */
#include <SFML/Graphics.hpp>
#include <variant>
/** @endcond */

enum class ObsEvents { collision, none };
enum class SpecEvents {shrink, expand, slow, speedup, bounce, colorChange, none};
enum class Effects { collision, explosion, score, none };
class Observer {
public:
    Observer(){}
    virtual void onNotify(const sf::Drawable* selfSubject, std::variant<ObsEvents, Effects, SpecEvents> event) = 0;
    virtual void onDangle(const sf::Drawable* selfSubject) = 0;
};
