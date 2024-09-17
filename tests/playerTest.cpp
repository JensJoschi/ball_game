#include "playerKB.h"
#include "gtest/gtest.h"
#include "command.h"
#include <sstream>
#include <sfml/Graphics.hpp>


class PlayerTest : public ::testing::Test {
    protected:
    PlayerTest() {
        PlayerKBSetupParams params{1.0, sf::Keyboard::Key::W, sf::Keyboard::Key::S};
        player = new PlayerKB(params);
        }
    ~PlayerTest() {
        delete player;
    }
    PlayerKB* player;
};

TEST_F(PlayerTest, actionWithNoEvents) {
    Command* c = player->action({});
    EXPECT_FALSE(c);
}

TEST_F(PlayerTest, actionWithWrongKey) {
    sf::Event event;
    event.type = sf::Event::KeyPressed;
    event.key.code = sf::Keyboard::Key::A;
    std::vector<sf::Event> events{event};
    Command* c = player->action(events);
    EXPECT_FALSE(c);
}

TEST_F(PlayerTest, actionWithWrongEvent) {
    sf::Event event;
    event.type = sf::Event::LostFocus;
    std::vector<sf::Event> events{event};
    Command* c = player->action(events);
    EXPECT_FALSE(c);
}

TEST_F(PlayerTest, actionWithCorrectKey) {
    sf::Event event;
    event.type = sf::Event::KeyPressed;
    event.key.code = sf::Keyboard::Key::W;
    std::vector<sf::Event> events{event};
    Command* c = player->action(events);
    EXPECT_TRUE(dynamic_cast<upCommand*>(c) != nullptr);

    event.key.code = sf::Keyboard::Key::S;
    events[0] = event;
    c = player->action(events);
    EXPECT_TRUE(dynamic_cast<downCommand*>(c) != nullptr);
}

TEST_F(PlayerTest, actionWith2CorrectKeys) {
    sf::Event event;
    event.type = sf::Event::KeyPressed;
    event.key.code = sf::Keyboard::Key::W;
    std::vector<sf::Event> events{event};
    sf::Event event2;
    event2.type = sf::Event::KeyPressed;
    event2.key.code = sf::Keyboard::Key::S;
    events.push_back(event2);
    Command* c = player->action(events);
    EXPECT_TRUE(dynamic_cast<upCommand*>(c) != nullptr); //early return on first key
}

TEST_F(PlayerTest, actionWithWrongAndCorrectKey){
    sf::Event event;
    event.type = sf::Event::KeyPressed;
    event.key.code = sf::Keyboard::Key::A;
    std::vector<sf::Event> events{event};
    sf::Event event2;
    event2.type = sf::Event::KeyPressed;
    event2.key.code = sf::Keyboard::Key::W;
    events.push_back(event2);
    Command* c = player->action(events);
    EXPECT_TRUE(dynamic_cast<upCommand*>(c) != nullptr);
}