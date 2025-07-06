cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)



## ---- find sources ----

set (SRC 
    "ai.cpp" "ball.cpp" "command.cpp"  "game.cpp" "gameState.cpp" "mainMenu.cpp" "MenuBase.cpp" "physicalObject.cpp" "playerKB.cpp"
    "playerMouse.cpp" "renderer.cpp" "options.cpp"
)
if(NOT SRC)
    message(FATAL_ERROR "SRC is empty")
endif()

#set also in parent scope so that tests can find them. Requires adding proper path:
set(DIR "${CMAKE_SOURCE_DIR}/src/")
foreach(SRC_FILE ${SRC})
    list(APPEND SRC_FILES "${DIR}${SRC_FILE}")
endforeach()
set (SRC_FILES ${SRC_FILES} PARENT_SCOPE)

#debug info
message(STATUS "SRC_FILES:")
foreach(SRC_FILE ${SRC_FILES})
    message(STATUS "${SRC_FILE}")
endforeach()


# ---- create binary ----
add_executable("ballgame"    ${SRC_FILES} "main.cpp" )
target_include_directories(ballgame PRIVATE ${SFML_INCLUDE_DIRS})
target_link_libraries(ballgame PRIVATE sfml-graphics sfml-window sfml-system)

# Copy the font file to the executable directory
add_custom_command(
    TARGET ballgame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/arial.ttf"
        "$<TARGET_FILE_DIR:ballgame>"
)