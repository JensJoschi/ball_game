
#pragma once
#include "enums.h"
#include "controller.h"
#include "playerKB.h"
#include "playermouse.h"
#include "ai.h"
#include <variant>

/**
* @brief Struct that contains the settings for a controller
 * Contains the type of controller, the general settings (sensitivity) and the settings that are specific to one controller type (e.g. keybinding)
 */
struct ControllerSetup {
    Controls control;
    ControllerSettings generalSettings;
    std::variant<PlayerMouseParams, PlayerKBSetupParams, AISetupParams> specificSettings;
};