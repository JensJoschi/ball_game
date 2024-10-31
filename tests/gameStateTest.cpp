#include "gameState.h"
#include "enums.h"
#include "renderer.h"
#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>


TEST(GameStateTest, crationAndDeletion){
    GameState gs;
    Renderer* r = new Renderer(nullptr, gs);
    ASSERT_EQ(r->getNoObjects(), 5);
    sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(10, 10));
    gs.addDrawable(items::BALL, shape);
    ASSERT_EQ(gs.drawables[2], shape);
    gs.onDangle(shape);
    ASSERT_EQ(gs.drawables[2], nullptr);
    gs.addDrawable(items::P1, shape);
    ASSERT_EQ(gs.drawables[0], shape);


    sf::CircleShape* circle = new sf::CircleShape(10);
    gs.addDrawable(items::SCORE1, circle);
    gs.onNotify(circle, shape);
    ASSERT_EQ(gs.drawables[3], shape);
}