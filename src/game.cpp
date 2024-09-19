#include "game.h"
#include "controller.h"
#include "ball.h"
#include "paddle.h"
#include "observer.h"
#include "command.h"
#include "playerKB.h"
#include "renderer.h"

/** @cond */
#include <cmath>
#include <iostream>
#include <cassert>
#include <memory>
#include <SFML/Graphics.hpp>
/** @endcond */

Game::Game(float extentX, float extentY, float player1Size, float player2Size, int ballVelocity)
    : m_window(sf::VideoMode(extentX, extentY), "Display!"),
      m_renderer(&m_window),
      m_pLeft(sf::Vector2f{20.0f, extentY/2}, player1Size, 10.0f),
      m_pRight(sf::Vector2f{extentX-20.0f, extentY/2}, player2Size, 10.0f),
      m_score1(0), m_score2(0), m_ballVelocity(ballVelocity)
    {
        srand(0);
        m_renderer.addDrawable(&m_pLeft.getShape());
        m_renderer.addDrawable(&m_pRight.getShape());
        m_renderer.display();
    }

void Game::start(){
    assignControls();
    addBall(m_ballVelocity);
}

void Game::run(){
    m_window.setFramerateLimit(60);
    sf::Clock clock;

    while (m_window.isOpen()) {
        sf::Time elapsed = clock.restart(); 
        std::vector<sf::Event> events;
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                m_window.close();}
            events.push_back(event);
        }
        update(events, elapsed);
        m_renderer.display();
        if (m_score1 == 10 || m_score2 == 10) {
            m_window.close();
        }
    }
}

void Game::update(const std::vector<sf::Event>& events, const sf::Time& elapsed){
    assert(m_ball);
    assert(m_c1);
    assert(m_c2);
    m_ball->moveBall(elapsed);
    bool someoneScored = handleCollisions(elapsed);
    if (someoneScored) {return;} 
    movePlayer(m_pLeft, m_c1.get(),  events, elapsed);
    movePlayer(m_pRight, m_c2.get(), events, elapsed);
}

void Game::assignControls(){
    PlayerKBSetupParams p1Params{250.0, sf::Keyboard::Key::W , sf::Keyboard::Key::S}; //temporary
    m_c1 = std::make_unique<PlayerKB>(p1Params);

    PlayerKBSetupParams p2Params{250.0,  sf::Keyboard::Key::Up , sf::Keyboard::Key::Down};
    m_c2 = std::make_unique<PlayerKB>(p2Params);
}

void Game::addBall(double speed){
    double direction = (rand() % 360) * M_PI / 180.0;  //to improve later
    sf::Vector2u windowSize = m_window.getSize();
    m_ball = std::make_unique<Ball>(sf::Vector2f{windowSize.x/2.0f, 
        windowSize.y/2.0f}, 10.0f, direction, speed);
    m_renderer.addDrawable(&m_ball->getShape());
}


bool Game::handleCollisions(const sf::Time& elapsed){
    if (m_pLeft.doesCollide(m_ball.get()->getShape()) || m_pRight.doesCollide(m_ball.get()->getShape())) {
        m_ball->rebounce(M_PI/2); //vertical paddle
        return false;
    }
    sf::Vector2u windowSize = m_window.getSize();
    sf::RectangleShape boundaries(sf::Vector2f(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)));
    if (m_ball.get()->doesCollide(boundaries)) { //within boundaries
        return false;
    }
    auto ballBounds = m_ball->getShape().getGlobalBounds();
    auto fieldBounds = boundaries.getGlobalBounds();
    if (ballBounds.top < fieldBounds.top || ballBounds.top + ballBounds.height > fieldBounds.top + fieldBounds.height) {
        m_ball->rebounce(0.0);
        while (ballBounds.top < fieldBounds.top || ballBounds.top + ballBounds.height > fieldBounds.top + fieldBounds.height){
            m_ball->moveBall(elapsed);
            ballBounds = m_ball->getShape().getGlobalBounds();
        }
        return false;
    }
    if (ballBounds.left < fieldBounds.left){
        m_score1++;
    } else {
        m_score2++;
    }
    addBall(m_ballVelocity); //also removes and deregisters the old ball
    return true;
}

void Game::movePlayer(Paddle& paddle, Controller* control, const std::vector<sf::Event>& events, const sf::Time& elapsed){
    assert(control);
    Command* e = control->action(events);
    if(e) e->execute(paddle, elapsed);
    auto pos = paddle.getShape().getGlobalBounds();
    auto windowSize = m_window.getSize();
    while (pos.top < 0) {
        downCommand d(1.0);
        d.execute(paddle, elapsed);
        pos = paddle.getShape().getGlobalBounds();
    }
    while (pos.top + pos.height > windowSize.y) {
        upCommand u(1.0);
        u.execute(paddle, elapsed);
        pos = paddle.getShape().getGlobalBounds();
    }
}