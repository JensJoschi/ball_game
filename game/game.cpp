#include "gameImpl.h"
#include "game.h"
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


Game::Game(const Options& options, InputSettings p1, InputSettings p2, sf::RenderWindow& window): m_impl(std::make_unique<GameImpl>(options, p1, p2, window)) {}

Game::~Game() = default;

void Game::run() { m_impl->run(); }
