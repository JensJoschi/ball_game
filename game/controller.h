#pragma once

#include "command.h"
/** @cond */
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
/** @endcond */




class Controller{
    public:
        Controller(const ControllerSettings opt) 
          : m_settings(opt),
            up(std::make_unique<upCommand>(opt.sensitivity)),
            down(std::make_unique<downCommand>(opt.sensitivity)) {
            assert(opt.sensitivity > 0);
        }
    virtual Command* action(const std::vector<sf::Event>& events) = 0;
    virtual ~Controller() = default;
    protected:
	const ControllerSettings m_settings;
	std::unique_ptr<Command> up; /**< Stores order to move upwards. See command.h. */
	std::unique_ptr<Command> down; /**< Stores order to move downwards. See command.h. */
};