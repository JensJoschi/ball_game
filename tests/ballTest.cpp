#include <gtest/gtest.h>
#include "ball.h"
#include <cmath>



class BallTest : public ::testing::Test {
    protected:
    BallTest() : ball(sf::Vector2f{0.0, 0.0}, 1,0, 1.0) {}
    Ball ball;
    double tolerance{0.01};

    void SetUp() override {
        // ball.addObserver(&observer);
    }
};

TEST_F(BallTest, setupTest){
    const sf::Shape& s = ball.getShape();
    auto c = s.getGlobalBounds();
    EXPECT_NEAR(c.left, 0.0, tolerance);
    EXPECT_NEAR(c.top, 0.0, tolerance);
    EXPECT_NEAR(c.width, 1.0, tolerance);
    EXPECT_NEAR(c.height, 1.0, tolerance);
}


TEST_F(BallTest, moveTest) {
    sf::Time oneSec = sf::seconds(1.0f);
    ball.moveBall(oneSec);
    auto c = ball.getShape().getGlobalBounds();
    EXPECT_NEAR(c.left, 1.0, tolerance);//+1 in x-direction
    EXPECT_NEAR(c.top, 0.0, tolerance);

    Ball ball2(sf::Vector2f{0.0, 0.0}, 1.0, 90*(M_PI/180), 1.0);
    ball2.moveBall(oneSec);
    auto c2 = ball2.getShape().getGlobalBounds();
    EXPECT_NEAR(c2.left, 0.0, tolerance); 
    EXPECT_NEAR(c2.top, 1.0, tolerance);//+1 in y-drection

    Ball ball3(sf::Vector2f{0.0, 0.0}, 1.0, 45 * (M_PI / 180), 1.0); // 45 degrees in radians
    ball3.moveBall(oneSec);
    auto c3 = ball3.getShape().getGlobalBounds();
    EXPECT_NEAR(c3.left, std::sqrt(2) / 2, tolerance);
    EXPECT_NEAR(c3.top, std::sqrt(2) / 2, tolerance); 
}

TEST_F(BallTest, rebounceTest_vertical) {
    sf::Time oneSec = sf::seconds(1.0f);
    auto initPos = ball.getShape().getGlobalBounds();
    ball.moveBall(oneSec);
    auto wallPos = ball.getShape().getGlobalBounds();
    ball.rebounce(90  * (M_PI/180)); 
    auto rbPos = ball.getShape().getGlobalBounds();
    ASSERT_TRUE((wallPos.left == rbPos.left) && (wallPos.top == rbPos.top));
    ball.moveBall(oneSec);//rebounce does not move the ball yet
    auto finalPos = ball.getShape().getGlobalBounds();
    EXPECT_NEAR(initPos.left, finalPos.left, tolerance);
    EXPECT_NEAR(initPos.top, finalPos.top, tolerance);
    EXPECT_TRUE((initPos.left != rbPos.left));

    Ball ball2(sf::Vector2f{67.0,14.0},1.0, 36 * (M_PI/180), 1.4);
    initPos = ball2.getShape().getGlobalBounds();
    ball2.moveBall(oneSec);
    wallPos = ball2.getShape().getGlobalBounds();
    ball2.rebounce(90* (M_PI/180));
    rbPos = ball2.getShape().getGlobalBounds();
    ASSERT_TRUE((wallPos.left == rbPos.left) && (wallPos.top == rbPos.top));
    ball2.moveBall(oneSec);
    finalPos = ball2.getShape().getGlobalBounds();
    EXPECT_NEAR(initPos.left, finalPos.left, tolerance);
    EXPECT_TRUE(finalPos.top > initPos.top); //moves back on x-axis, and further up on y-axis
    ball2.moveBall(oneSec);
    auto finalPos2 = ball2.getShape().getGlobalBounds();
    EXPECT_TRUE((finalPos2.left < finalPos.left) && (finalPos2.top > finalPos.top));
}


TEST_F(BallTest, rebounceTest_angle) {
    sf::Time oneSec = sf::seconds(1.0f);
    auto initPos = ball.getShape().getGlobalBounds();
    ball.moveBall(oneSec);
    auto wallPos = ball.getShape().getGlobalBounds();
    ball.rebounce(30  * (M_PI/180)); 
    ball.moveBall(oneSec);
    auto finalPos = ball.getShape().getGlobalBounds();

    Ball ball2(sf::Vector2f{0.0, 0.0}, 1,0, 1.0);
    ball2.moveBall(oneSec);
    ball2.rebounce(40  * (M_PI/180)); 
    ball2.moveBall(oneSec);
    auto finalPos2 = ball2.getShape().getGlobalBounds();
    EXPECT_TRUE(finalPos.left > wallPos.left);
    EXPECT_TRUE(finalPos.top > wallPos.top);
    EXPECT_TRUE(finalPos2.left < finalPos.left);
    EXPECT_TRUE(finalPos2.top > finalPos.top);
}