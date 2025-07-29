#include "game.h"
#include "gameImpl.h"
#include "options.h"
#include "inputSettings.h"
#include "ball.h"
#include "paddle.h"
#include "controller.h"
#include "ai.h"
#include "playerKB.h"
#include "playermouse.h"
#include "enums.h"
#include "gameState.h"
#include "observer.h"
#include "renderer.h"
#include "sound.h"

/** @cond */
#include <cmath>
#include <iostream>
#include <cassert>
#include <memory>
#include <SFML/Graphics.hpp>
#include <variant>
/** @endcond */


GameImpl::GameImpl(const Options& options, InputSettings p1, InputSettings p2, sf::RenderWindow& window)
    : m_window(&window),
    m_gameState(),
    m_renderer(m_window, m_gameState),
    m_pLeft(sf::Vector2f{ 20.0f, static_cast<float>(m_window->getSize().y / 2.0) }, options.player1Size, 10.0f),
    m_pRight(sf::Vector2f{ m_window->getSize().x - 20.0f,static_cast<float>(m_window->getSize().y / 2.0) }, options.player2Size, 10.0f),
    m_score1(0), m_score2(0), m_ballVelocity(options.ballVelocity), m_score1Text(), m_score2Text(),
    m_c1(createController(std::move(p1), window)), m_c2(createController(std::move(p2), window)),
    m_sound()
{
    srand(0);
    if (!m_font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font\n";
    }
    m_score1Text.setFont(m_font);
    m_score1Text.setString("0");
    m_score1Text.setCharacterSize(24);
    m_score1Text.setFillColor(sf::Color::White);
    m_score1Text.setPosition(10.0f, 10.0f); // top-left corner

    m_score2Text.setFont(m_font);
    m_score2Text.setString("0");
    m_score2Text.setCharacterSize(24);
    m_score2Text.setFillColor(sf::Color::White);
    m_score2Text.setPosition(m_window->getSize().x - 30.0f, 10.0f); // top-right corner

    m_gameState.addDrawable(items::P1, &m_pLeft.getShape());
    m_gameState.addDrawable(items::P2, &m_pRight.getShape());
    m_gameState.addDrawable(items::SCORE1, &m_score1Text);
    m_gameState.addDrawable(items::SCORE2, &m_score2Text);
    m_pLeft.addObserver(&m_gameState);
    m_pLeft.addObserver(&m_sound);
    m_pRight.addObserver(&m_gameState);
    m_pRight.addObserver(&m_sound);
    auto c = dynamic_cast<AI*> (m_c1.get());
    if (c) c->connect(&m_gameState); //AI needs to "see" the game
    c = dynamic_cast<AI*> (m_c2.get());
    if (c) c->connect(&m_gameState);

    addBall(m_ballVelocity);
    m_renderer.display();
}

void GameImpl::run() {
    sf::Clock clock;
    while (m_window->isOpen()) {
        sf::Time elapsed = clock.restart();
        std::vector<sf::Event> events;
        sf::Event event;
        while (m_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window->close();
            }
            events.push_back(event);
        }
        m_window->clear();
        bool finished = update(events, elapsed);
        if (finished) return;
    }
}

bool GameImpl::update(const std::vector<sf::Event>& events, const sf::Time& elapsed) {
    assert(m_ball);
    assert(m_c1);
    assert(m_c2);
    if (m_gameState.isCollisionThresReached()) {
        m_ballVelocity += 25;
        addBall(m_ballVelocity);
        return false;
    }
    else {
        m_ball->move(elapsed);
        bool someoneScored = handleCollisions(elapsed);
        if (!someoneScored) {
            movePlayer(m_pLeft, m_c1.get(), events, elapsed);
            movePlayer(m_pRight, m_c2.get(), events, elapsed);
        }
        else {
            m_sound.onNotify(&m_ball->getShape(), obsEvents::score);
        }

        m_renderer.display();
        if (m_score1 == 10 || m_score2 == 10) {
            return true;
        }
        else return false;
    }
}

void GameImpl::addBall(double speed) {
    double direction = (rand() % 360) * M_PI / 180.0;  //to improve later
    sf::Vector2u windowSize = m_window->getSize();
    m_ball = std::make_unique<Ball>(sf::Vector2f{ windowSize.x / 2.0f,
        windowSize.y / 2.0f }, 10.0f, direction, speed);
    m_ball->addObserver(&m_gameState);
    m_ball->addObserver(&m_sound);
    m_gameState.addDrawable(items::BALL, &m_ball->getShape());
}


bool GameImpl::handleCollisions(const sf::Time& elapsed) {
    if (m_pLeft.doesCollide(m_ball.get()->getShape()) || m_pRight.doesCollide(m_ball.get()->getShape())) {
        m_ball->rebounce(M_PI / 2); //vertical paddle
        return false;
    }
    sf::Vector2u windowSize = m_window->getSize();
    sf::RectangleShape boundaries(sf::Vector2f(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)));
    if (m_ball->getShape().getGlobalBounds().intersects(boundaries.getGlobalBounds())) {
        return false;
    }
    auto ballBounds = m_ball->getShape().getGlobalBounds();
    auto fieldBounds = boundaries.getGlobalBounds();
    if (ballBounds.top < fieldBounds.top || ballBounds.top + ballBounds.height > fieldBounds.top + fieldBounds.height) {
        m_ball->doesCollide(m_ball->getShape()); //will increase the collision counter
        m_ball->rebounce(0.0);
        while (ballBounds.top < fieldBounds.top || ballBounds.top + ballBounds.height > fieldBounds.top + fieldBounds.height) {
            m_ball->move(elapsed);
            ballBounds = m_ball->getShape().getGlobalBounds();
        }
        return false;
    }
    if (ballBounds.left < fieldBounds.left) {
        m_score2++;
        m_score2Text.setString(std::to_string(m_score2));
    }
    else {
        m_score1++;
        m_score1Text.setString(std::to_string(m_score1));
    }
    addBall(m_ballVelocity); //also removes and deregisters the old ball
    return true;
}

void GameImpl::movePlayer(Paddle& paddle, Controller* control, const std::vector<sf::Event>& events, const sf::Time& elapsed) {
    assert(control);
    Command* e = control->action(events);
    if (e) e->execute(paddle, elapsed);
    auto pos = paddle.getShape().getGlobalBounds();
    auto windowSize = m_window->getSize();
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

template <typename>
inline constexpr bool always_false = false;

std::unique_ptr<Controller> GameImpl::createController(InputSettings setup, sf::RenderWindow& window) {
    auto general = std::move(setup.general);
    auto specific = std::move(setup.specific);
    auto visit_fcn = [gen = std::move(general), &window](auto&& spec) -> std::unique_ptr<Controller> {
        using T = std::decay_t<decltype(spec)>;
        if constexpr (std::is_same_v<T, PlayerKBSetupParams>) {
            return std::make_unique<PlayerKB>(std::move(gen), std::forward<T>(spec));
        }
        else if constexpr (std::is_same_v<T, PlayerMouseParams>) {
            return std::make_unique<PlayerMouse>(std::move(gen), std::forward<T>(spec), window);
        }
        else if constexpr (std::is_same_v<T, AISetupParams>) {
            return std::make_unique<AI>(std::move(gen), std::forward<T>(spec));
        }
        else {
            static_assert(always_false<T>, "Unknown controller type");
        }
        };
    return std::visit(visit_fcn, std::move(specific));
}