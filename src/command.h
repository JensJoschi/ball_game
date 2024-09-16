#ifndef COMMAND_H
#define COMMAND_H

#include "physicalObject.h"
/** @cond */
#include <cassert>
/** @endcond */

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

#endif // COMMAND_H