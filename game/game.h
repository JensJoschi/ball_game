#pragma once

#include "ball.h"
#include "controller.h"
#include "controllerSetup.h"
#include "enums.h"
#include "gameState.h"
#include "observer.h"
#include "options.h"
#include "paddle.h"
#include "powerItem.h"
#include "renderer.h"
#include "sound.h"

/** @cond */
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <variant>
#include <random>
/** @endcond */

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
	explicit Game(const Options& options, ControllerSetup p1, ControllerSetup p2, sf::RenderWindow& window);

    ~Game();

    /**
	* @brief run 1 time step
	 * returns true if game over.
	 */
    bool update(const std::vector<sf::Event>& events, const sf::Time& elapsed);

    private:
    sf::RenderWindow* m_window;
	GameState m_gameState; /**< contains current state (position etc) of all game objects */
	Renderer m_renderer;
	std::unique_ptr<Controller> m_c1; /**< Controller for player 1. May be controlled by mouse, keyboard, AI .. */
	std::unique_ptr<Controller> m_c2; /**< Controller for player 2. May be controlled by mouse, keyboard, AI .. */
    Paddle m_pLeft;
    Paddle m_pRight;
    std::unique_ptr<Ball> m_ball;
	std::unique_ptr<PowerItemBASE> m_powerItem;

    int m_score1;
    sf::Text m_score1Text;
    int m_score2;
    sf::Text m_score2Text;
    double m_ballVelocity;
    sf::Font m_font;

    Sound m_sound;
    std::mt19937 rng;
    void addBall(double speed);
	void addItem();
    /**
	* @brief Check for collisions and update game
    * Updates points, rebounces ball if neccessary
	* returns true if someone scored
	*/
    bool handleCollisions(const sf::Time& elapsed);
    void handleSpecialEvents();
    void movePlayer(Paddle& paddle, Controller* control, const std::vector<sf::Event>& events, const sf::Time& elapsed);
    Controller* createController(ControllerSetup setup, sf::RenderWindow& window);
};

