#pragma once

#include "options.h"
#include "inputSettings.h"

/** @cond */
#include <SFML/Graphics.hpp>
/** @endcond */

#ifdef BUILDING_GAME_DLL
#define GAME_API __declspec(dllexport)
#else
#define GAME_API __declspec(dllimport)
#endif

class GameImpl;
/*! 
    *  \brief Game class
    *  \details
    *  This class contains the court, the ball and the players. 
    */
class Game{
    public:
    /**
     * @brief Construct a new Game object
     *
	 * @param options General game settings such as ball velocity and paddle sizes
	 * @param p1 Controller setup for player 1 (type, keys if applicable, difficulty of AI etc.)
	 * @param p2 Controller setup for player 2 (type, keys if applicable, difficulty of AI etc.)
	 * @param window The window to render the game in
	 */
	GAME_API explicit Game(const Options& options, InputSettings p1, InputSettings p2, sf::RenderWindow& window);

    GAME_API ~Game();

    GAME_API void run();

private:
	std::unique_ptr<GameImpl> m_impl;
};

