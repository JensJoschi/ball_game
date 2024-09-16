#ifndef GAME_H
#define GAME_H

#include "ball.h"
#include "paddle.h"
#include "observer.h"
#include "controller.h"
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
    Game(float extentX, float extentY, float player1Size, float player2Size, int ballVelocity);

    void start();

    void run();

    private:
    sf::RenderWindow m_window;
    std::unique_ptr<Controller> m_c1; 
    std::unique_ptr<Controller> m_c2;
    Paddle m_pLeft;
    Paddle m_pRight;
    std::unique_ptr<Ball> m_ball;

    int m_score1;
    int m_score2;

    double m_ballVelocity;

    void assignControls();
    void addBall(double speed);
};

#endif // FIELD_H
