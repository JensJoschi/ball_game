#pragma once
#include "inputsettings.h"
#include "command.h"
/** @cond */
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
/** @endcond */

class Controller{
    public:
    Controller(ControllerSettings opt) 
          : m_settings(std::move(opt)),
            up(std::make_unique<upCommand>(m_settings.sensitivity)),
            down(std::make_unique<downCommand>(m_settings.sensitivity)) {
            assert(m_settings.sensitivity > 0);
        }
    Controller(const Controller&) = delete;
    Controller& operator=(const Controller&) = delete;
    Controller(Controller&&) = default;
    Controller& operator=(Controller&&) = default;

    virtual Command* action(const std::vector<sf::Event>& events) = 0;
    virtual ~Controller() = default;
    

    protected:
	
    const ControllerSettings m_settings;
	std::unique_ptr<Command> up; /**< Stores order to move upwards. See command.h. */
	std::unique_ptr<Command> down; /**< Stores order to move downwards. See command.h. */
};