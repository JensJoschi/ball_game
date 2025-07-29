#game/cmakelists.txt
message(STATUS "Configuring game dll...")

set (GAMEFILES 
    "ai.cpp" 
    "ball.cpp" 
    "command.cpp"  
    "game.cpp" 
    "gameState.cpp" 
    "physicalObject.cpp" 
    "playerKB.cpp"
    "playerMouse.cpp" 
    "renderer.cpp"
)
if(NOT GAMEFILES)
    message(FATAL_ERROR "source directory(game) is empty")
endif()
message(STATUS "SRC_FILES:")
foreach(SRC_FILE ${GAMEFILES})
    message(STATUS "${SRC_FILE}")
endforeach()

add_library(game SHARED ${GAMEFILES})
target_compile_definitions(game PRIVATE BUILDING_GAME_DLL)
target_link_libraries(game PRIVATE sfml-graphics sfml-window sfml-system)
target_include_directories(game PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR} 
    ${CMAKE_SOURCE_DIR}/include
)

add_library(game_static STATIC ${GAMEFILES}) #for unit tests
target_link_libraries(game_static PRIVATE sfml-graphics sfml-window sfml-system)
target_include_directories(game_static PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR} 
    ${CMAKE_SOURCE_DIR}/include
)

set_target_properties(game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/${CONFIG_TYPE}"  
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/${CONFIG_TYPE}" 
)