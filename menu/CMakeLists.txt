#menu/cmakeLists.txt
message(STATUS "Configuring menu dll...")

set (MENUFILES 
    "menu.cpp" #API
    "menuBase.cpp"
    "mainMenu.cpp"
    "optionMenu.cpp"
)
if(NOT MENUFILES)
    message(FATAL_ERROR "no files to compile in menu")
endif()
message(STATUS "SOURCE FILES:")
foreach(FILE IN LISTS MENUFILES)
    message(STATUS "${FILE}")
endforeach()

add_library(menu SHARED ${MENUFILES})
target_compile_definitions(menu PRIVATE BUILDING_MENU_DLL)

target_link_libraries(menu PRIVATE sfml-graphics sfml-window sfml-system)
target_include_directories(menu PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR} 
    ${CMAKE_SOURCE_DIR}/include
)
set_target_properties(menu PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/${CONFIG_TYPE}"  
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/${CONFIG_TYPE}" 
)