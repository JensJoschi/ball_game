#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "command.h"
/** @cond */
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
/** @endcond */

class Controller{
    public:
    Controller(double moveby = 0.0): 
        up(std::make_unique<upCommand>(moveby)), 
        down(std::make_unique<downCommand>(moveby)){}
    virtual Command* action(const std::vector<sf::Event>& events) = 0;
    virtual ~Controller() = default;
    protected:
    std::unique_ptr<Command> up;
    std::unique_ptr<Command> down;
};
#endif // CONTROLLER_H