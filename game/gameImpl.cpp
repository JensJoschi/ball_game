#include "game.h"

#include "ai.h"
#include "ball.h"
#include "command.h"
#include "controller.h"
#include "controllerSetup.h"
#include "enums.h"
#include "gameState.h"
#include "options.h"
#include "paddle.h"
#include "playerKB.h"
#include "playermouse.h"
#include "renderer.h"

/** @cond */
#include <cmath>
#include <iostream>
#include <cassert>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <random>
/** @endcond */


Game::Game(const Options& options, ControllerSetup p1, ControllerSetup p2, sf::RenderWindow& window)
: m_window(&window),
  m_gameState(),
  m_renderer(m_window, m_gameState),
  m_pLeft(sf::Vector2f{20.0f, static_cast<float>(m_window->getSize().y/2.0)}, options.player1Size, 10.0f),
  m_pRight(sf::Vector2f{m_window->getSize().x - 20.0f,static_cast<float>(m_window->getSize().y/2.0)}, options.player2Size, 10.0f),
  m_score1(0), m_score2(0), m_ballVelocity(options.ballVelocity), m_score1Text(), m_score2Text(),
  m_c1(createController(std::move(p1), window)), m_c2(createController(std::move(p2), window)),
	m_sound(), rng(std::random_device()())
{
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
	if (c) c->connect(&m_gameState);
	c = dynamic_cast<AI*> (m_c2.get());
	if (c) c->connect(&m_gameState);

    addBall(m_ballVelocity);
    addItem();
    m_renderer.display();
}

Game::~Game() {
	//if (m_powerItem) delete m_powerItem;
}

bool Game::update(const std::vector<sf::Event>& events, const sf::Time& elapsed){
    assert(m_ball);
    assert(m_c1);
    assert(m_c2);
	if (m_gameState.isCollisionThresReached()) {
        m_ballVelocity += 25;
        addBall(m_ballVelocity);
		addItem();
		return false;
    }
    else {
        handleSpecialEvents();
        m_ball->move(elapsed);
        bool someoneScored = handleCollisions(elapsed);
        if (!someoneScored) {
            movePlayer(m_pLeft, m_c1.get(), events, elapsed);
            movePlayer(m_pRight, m_c2.get(), events, elapsed);
        }
        else {
            m_sound.onNotify(&m_ball->getShape(), Effects::score);
        }

        m_renderer.display();
        if (m_score1 == 10 || m_score2 == 10) {
            return true;
        }
        else return false;
    }
}

void Game::addBall(double speed){
    double direction = (rand() % 360) * M_PI / 180.0;  //to improve later
    sf::Vector2u windowSize = m_window->getSize();
    m_ball = std::make_unique<Ball>(sf::Vector2f{windowSize.x/2.0f, 
        windowSize.y/2.0f}, 10.0f, direction, speed);
    m_ball->addObserver(&m_gameState);
	m_ball->addObserver(&m_sound);
    m_gameState.addDrawable(items::BALL, &m_ball->getShape());
}

void Game::addItem() {
	sf::Vector2u windowSize = m_window->getSize();
	sf::Vector2f pos = sf::Vector2f(std::uniform_int_distribution <int>(10, windowSize.x - 10)(rng), std::uniform_int_distribution <int>(10, windowSize.y - 10)(rng));
	ItemType itype = static_cast<ItemType>(std::uniform_int_distribution <int>(0, static_cast<int>(ItemType::COUNT)-1)(rng));
    switch (itype){
	case ItemType::Shrink:
		m_powerItem = std::make_unique<PowerItem<ItemType::Shrink>>(pos);
		break;
	case ItemType::Enlarge:
		m_powerItem = std::make_unique<PowerItem<ItemType::Enlarge>>(pos);
		break;
	case ItemType::SpeedUp:
		m_powerItem = std::make_unique<PowerItem<ItemType::SpeedUp>>(pos);
		break;
	case ItemType::SlowDown:
		m_powerItem = std::make_unique<PowerItem<ItemType::SlowDown>>(pos);
		break;
	case ItemType::ChangeColor:
		m_powerItem = std::make_unique<PowerItem<ItemType::ChangeColor>>(pos);
		break;
	case ItemType::Bounce:
		m_powerItem = std::make_unique<PowerItem<ItemType::Bounce>>(pos);
		break;
	}
    m_gameState.addDrawable(items::POWERITEM, &m_powerItem->getShape());
    m_powerItem->addObserver(&m_gameState);
    m_powerItem->addObserver(&m_sound);
}


bool Game::handleCollisions(const sf::Time& elapsed){
	if(m_powerItem && m_ball->doesCollide(m_powerItem->getShape())) {
            m_powerItem->vanish();
            m_powerItem.reset();
		}

    if (m_pLeft.doesCollide(m_ball.get()->getShape()) || m_pRight.doesCollide(m_ball.get()->getShape())) {
        m_ball->rebounce(M_PI/2); //vertical paddle
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
        while (ballBounds.top < fieldBounds.top || ballBounds.top + ballBounds.height > fieldBounds.top + fieldBounds.height){
            m_ball->move(elapsed);
            ballBounds = m_ball->getShape().getGlobalBounds();
        }
        return false;
    }
    if (ballBounds.left < fieldBounds.left){
        m_score2++;
        m_score2Text.setString(std::to_string(m_score2));
    } else {
        m_score1++;
        m_score1Text.setString(std::to_string(m_score1));
    }
    addBall(m_ballVelocity); //also removes and deregisters the old ball
    return true;
}

void Game::movePlayer(Paddle& paddle, Controller* control, const std::vector<sf::Event>& events, const sf::Time& elapsed){
    assert(control);
    Command* e = control->action(events);
    if(e) e->execute(paddle, elapsed);
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

Controller* Game::createController(ControllerSetup setup, sf::RenderWindow& window) {
    switch (setup.control) {
    case Controls::KB: {
		assert(std::holds_alternative<PlayerKBSetupParams>(setup.specificSettings));
		return new PlayerKB(std::move(setup.generalSettings), std::move(std::get<PlayerKBSetupParams>(setup.specificSettings)));
    }
    case Controls::MOUSE:{
		assert(std::holds_alternative<PlayerMouseParams>(setup.specificSettings));
		return new PlayerMouse(std::move(setup.generalSettings), std::move(std::get<PlayerMouseParams>(setup.specificSettings)));
    }
    case Controls::AI:{
		assert(std::holds_alternative<AISetupParams>(setup.specificSettings));
		return new AI(std::move(setup.generalSettings), std::move(std::get<AISetupParams>(setup.specificSettings)));
	}
    default:
        return nullptr;
    }
}

void Game::handleSpecialEvents() {
    auto e = m_gameState.getSpecialEvent();
    switch (e) {
    case SpecEvents::none:
        break;
    case SpecEvents::bounce:
        m_ball->rebounce(M_PI / 2);
        break;
    case SpecEvents::shrink:
        m_pLeft.changeSize(0.5);
        m_pRight.changeSize(0.5);
        break;
    case SpecEvents::expand:
        m_pLeft.changeSize(2);
        m_pRight.changeSize(2);
        break;
    case SpecEvents::colorChange:
        m_gameState.setColor(sf::Color(std::uniform_int_distribution <int>(0, 255)(rng), std::uniform_int_distribution <int>(0, 255)(rng), std::uniform_int_distribution <int>(0, 255)(rng)));
		break;
    case SpecEvents::slow:
		m_ball->changeSpeed(0.5);
		break;
    case SpecEvents::speedup:
		m_ball->changeSpeed(1.5);
		break;
    }
}