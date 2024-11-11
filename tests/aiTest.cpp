#include "ai.h"
#include "gameState.h"
#include "paddle.h"
#include "ball.h"
#include <gtest/gtest.h>

TEST(aitest, movement){
    GameState gs;
    Ball ball(sf::Vector2f(0, 0), 1, M_PI/2, 3.0);
    Paddle p1(sf::Vector2f(0, 0), 1.0, 0.1);
    gs.addDrawable(items::BALL, &ball.getShape());
    gs.addDrawable(items::P1, &p1.getShape());
	ControllerSettings general{ 250.0 };
    AISetupParams params{items::P1 };
    AI ai(general, params);
	ai.connect(&gs);
    auto p1pos = static_cast<const sf::Shape*>(gs.drawables[static_cast<int>(items::P1)])->getPosition();
    EXPECT_EQ(p1pos.y, 0.0);
    auto ballpos = static_cast<const sf::Shape*>(gs.drawables[static_cast<int>(items::BALL)])->getPosition();
    EXPECT_EQ(ballpos.y, 0.0);
    ball.move(sf::seconds(1));
    ballpos = static_cast<const sf::Shape*>(gs.drawables[static_cast<int>(items::BALL)])->getPosition();
    EXPECT_EQ(ballpos.y, 3.0);
    Command* m = ai.action({});
    EXPECT_TRUE(dynamic_cast<downCommand*>(m));
}