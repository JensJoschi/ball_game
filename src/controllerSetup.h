
#pragma once
#include "enums.h"
#include "controller.h"
#include "playerKB.h"
#include "playermouse.h"
#include "ai.h"
#include <variant>


struct ControllerSetup {
    Controls control;
    ControllerSettings generalSettings;
    std::variant<PlayerMouseParams, PlayerKBSetupParams, AISetupParams> specificSettings;
};