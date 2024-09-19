#include "command.h"
#include "gtest/gtest.h"
#include "paddle.h"


TEST (CommandTest, upCommandTest){
    sf::Time oneSec = sf::seconds(1.0f);
    Paddle obj(sf::Vector2f{27.0, -4.0}, 2, 0.1);
    auto before = obj.getShape().getGlobalBounds();
    upCommand up(2.0);
    up.execute(obj, oneSec);
    auto after = obj.getShape().getGlobalBounds();
    EXPECT_EQ(after.left, before.left);
    EXPECT_EQ(after.top, before.top - 2.0);
}

TEST (CommandTest, downCommandTest){
    sf::Time oneSec = sf::seconds(1.0f);
    Paddle obj(sf::Vector2f{27.0, -4.0}, 2, 0.1);
    auto before = obj.getShape().getGlobalBounds();
    downCommand down(2.0);
    down.execute(obj, oneSec);
    auto after = obj.getShape().getGlobalBounds();
    EXPECT_EQ(after.left, before.left);
    EXPECT_EQ(after.top, before.top + 2.0);
}