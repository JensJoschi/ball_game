#include "gameState.h"
#include "renderer.h"
#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>


TEST(GameStateTest, crationAndDeletion){
    GameState gs;
    Renderer* r = new Renderer(nullptr, gs);
    sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(10, 10));
    gs.addDrawable(shape);
    ASSERT_EQ(r->getNoObjects(), 1);
    gs.onDangle(shape);
    ASSERT_EQ(r->getNoObjects(), 0);
    gs.addDrawable(shape);
    ASSERT_EQ(r->getNoObjects(), 1);
    delete(shape); //destructor calls onDangle
    ASSERT_EQ(r->getNoObjects(), 0);

    sf::CircleShape* circle = new sf::CircleShape(10);
    gs.addDrawable(shape);
    gs.onNotify(shape, circle);
    ASSERT_EQ(r->getNoObjects(), 1); //is now a circle, not a rectangle
}