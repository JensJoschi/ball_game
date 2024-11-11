#pragma once
#include "observer.h"
#include "enums.h"

/** @cond */
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <vector>
/** @endcond */


/** @brief GameState class
 *
 * Game state tracks the current state of all objects (position etc). This central registry ensures that all entities react to the same information while avoiding coupling.
 * 
 * This class is an observer. In principle, one could let all objects of the game send a signal when they are moved (via the observer's onNotify() function), and the gameState could relay this information/present it to other classes.
 * But this would elicit a lot of signals. Instead this class holds a const pointer to all objects, so the position can be read directly, and the onNotify is only required for rarer special events (such as collisions).
 * Ondangle() deregisters objects when they are destroyed (called in the destructor of PhysicalObject), as in other Observer classes.
 * \note onNotify should be used for counting the total number of collisions in the game. To-do. 
 */
class GameState: public Observer{
    public: 
    GameState();
	~GameState() = default; //drawables are not owned by GameState.
    void addDrawable(items i, const sf::Drawable* newD);
	void exchangeDrawable(const sf::Drawable* oldD, const sf::Drawable* newD);
    bool isCollisionThresReached();
    int getCollision() const;
    virtual void onNotify(const sf::Drawable* selfSubject, obsEvents e) override; //to be renamed exchangeDrawable, no override
    virtual void onDangle(const sf::Drawable* selfSubject) override;
    std::vector<const sf::Drawable*> drawables;
private:
    int collisionCount;
    bool act;
};

