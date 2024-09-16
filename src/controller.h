#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "command.h"
/** @cond */
#include <memory>
/** @endcond */

class Controller{
    public:
    Controller(double moveby = 0.0);
    virtual Command* action() = 0;
    virtual ~Controller() = default;
    protected:
    std::unique_ptr<Command> up;
    std::unique_ptr<Command> down;
};
#endif // CONTROLLER_H