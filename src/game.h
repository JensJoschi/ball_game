#pragma once

#include "ball.h"
#include "paddle.h"
#include "observer.h"
#include "controller.h"
#include "gameState.h"
#include "renderer.h"
#include "options.h"
#include "menu.h" //for enum Controls

/** @cond */
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
/** @endcond */


/*! 
    *  \brief Game class
    *  \details
    *  This class contains the court, the ball and the players. 
    */
class Game{
    public:


    //Game(const Options& options, Controller* p1, Controller* p2, sf::RenderWindow& window);
	explicit Game(const Options& options, std::pair<Controls, ControllerSettings*> p1, std::pair<Controls, ControllerSettings*> p2, sf::RenderWindow& window);
    bool update(const std::vector<sf::Event>& events, const sf::Time& elapsed);

    private:
    sf::RenderWindow* m_window;
    GameState m_gameState;
    Renderer m_renderer;
    std::unique_ptr<Controller> m_c1; 
    std::unique_ptr<Controller> m_c2;
    Paddle m_pLeft;
    Paddle m_pRight;
    std::unique_ptr<Ball> m_ball;

    int m_score1;
    sf::Text m_score1Text;
    int m_score2;
    sf::Text m_score2Text;
    double m_ballVelocity;
    sf::Font m_font;

    void addBall(double speed);
    bool handleCollisions(const sf::Time& elapsed);
    void movePlayer(Paddle& paddle, Controller* control, const std::vector<sf::Event>& events, const sf::Time& elapsed);
    Controller* createController(Controls control, ControllerSettings* opt, sf::RenderWindow& window);
};

