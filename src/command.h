#pragma once

#include "physicalObject.h"
/** @cond */
#include <cassert>
/** @endcond */


/** 
* @brief Command class
* 
* This class encapsulates the execution of a command (such moving a paddle). In contrast to a simple execute() function, a command object can be 
* stored, queued or altered, and executed at a later time.
*/

class Command{
    public:
    Command(double moveBy);
    virtual void execute(PhysicalObject&, const sf::Time& elapsed) = 0;
    virtual ~Command() = default;
    protected: 
    double m_moveBy;
};

class upCommand : public Command{
    public:
    upCommand(double moveBy): Command(moveBy){}
    void execute(PhysicalObject&, const sf::Time& elapsed) override;
};

class downCommand : public Command{
    public:
    downCommand(double moveBy): Command(moveBy){}
    void execute(PhysicalObject&, const sf::Time& elapsed) override;
};