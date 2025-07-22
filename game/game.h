#pragma once

#include "options.h"
#include "inputSettings.h"
#include "ball.h"
#include "paddle.h"
#include "controller.h"
#include "enums.h"
#include "gameState.h"
#include "observer.h"
#include "renderer.h"
#include "sound.h"

/** @cond */
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <variant>
#include <vector>
/** @endcond */

#ifdef BUILDING_GAME_DLL
#define GAME_API __declspec(dllexport)
#else
#define GAME_API __declspec(dllimport)
#endif

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

    GAME_API ~Game() = default;

    GAME_API void run();

    /**
	* @brief run 1 time step
	 * returns true if game over.
	 */
    bool update(const std::vector<sf::Event>& events, const sf::Time& elapsed);

    private:
        // pimpl - to do
    sf::RenderWindow* m_window;
	GameState m_gameState; /**< contains current state (position etc) of all game objects */
	Renderer m_renderer;
	std::unique_ptr<Controller> m_c1; /**< Controller for player 1. May be controlled by mouse, keyboard, AI .. */
	std::unique_ptr<Controller> m_c2; /**< Controller for player 2. May be controlled by mouse, keyboard, AI .. */
    Paddle m_pLeft;
    Paddle m_pRight;
    std::unique_ptr<Ball> m_ball;

    int m_score1;
    sf::Text m_score1Text;
    int m_score2;
    sf::Text m_score2Text;
    double m_ballVelocity;
    sf::Font m_font;

    Sound m_sound;
    void addBall(double speed);
    /**
	* @brief Check for collisions and update game
    * Updates points, rebounces ball if neccessary
	* returns true if someone scored
	*/
    bool handleCollisions(const sf::Time& elapsed);
    void movePlayer(Paddle& paddle, Controller* control, const std::vector<sf::Event>& events, const sf::Time& elapsed);
    std::unique_ptr<Controller> createController(InputSettings setup, sf::RenderWindow& window);
};

