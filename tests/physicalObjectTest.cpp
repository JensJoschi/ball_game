#include <gtest/gtest.h>
#include "physicalObject.h"


class PhysObTest : public ::testing::Test {
    protected:
    PhysObTest() : physob(std::make_unique<sf::RectangleShape>(sf::Vector2f{1.0, 1.0})) {}
    PhysicalObject physob;
    double tolerance{0.01};

    void SetUp() override {
        // physob.addObserver(&observer);
    }
};
TEST_F(PhysObTest, buildTest){
    auto& s{ physob.getShape()};
    auto c = s.getGlobalBounds();
    EXPECT_NEAR(c.left, 0.0, tolerance);
    EXPECT_NEAR(c.top, 0.0, tolerance);
    EXPECT_NEAR(c.width, 1.0, tolerance);
    EXPECT_NEAR(c.height, 1.0, tolerance);
}

TEST_F(PhysObTest, doesCollideShape){
    sf::RectangleShape shape(sf::Vector2f{1.0, 1.0});
    shape.setPosition(0.0, 0.5);
    EXPECT_TRUE(physob.doesCollide(shape));
    sf::RectangleShape shape2(sf::Vector2f{1.0, 1.0});
    shape2.setPosition(0.0, 1.5);
    EXPECT_FALSE(physob.doesCollide(shape2));
}

TEST_F(PhysObTest, doesCollidePhysOb){
    std::unique_ptr<sf::RectangleShape> shape = std::make_unique<sf::RectangleShape>(sf::Vector2f{1.0, 1.0});
    shape->setPosition(0.0, 0.5);
    PhysicalObject physob2(std::move(shape));
    EXPECT_TRUE(physob.doesCollide(physob2));
    std::unique_ptr<sf::RectangleShape> shape2 = std::make_unique<sf::RectangleShape>(sf::Vector2f{1.0, 1.0});
    shape2->setPosition(0.0, 1.5);
    PhysicalObject physob3(std::move(shape2));
    EXPECT_FALSE(physob.doesCollide(physob3));
}

//no test of move yet, move function is protected. Will be tested in derived classes / once there is a command pattern