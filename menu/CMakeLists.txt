set (SFML_DIR "C:/tools/SFML-2.6.2/lib/cmake/SFML")
find_package(SFML 2.6.2 COMPONENTS graphics window system REQUIRED)

set (MENUFILES 
    "menu.cpp" #API
    "menuBase.cpp"
    "mainMenu.cpp"
    "optionMenu.cpp"
)
if(NOT MENUFILES)
    message(FATAL_ERROR "no files to compile in menu")
endif()

#debug info
message(STATUS "SRC_FILES:")
foreach(FILE IN LISTS MENUFILES)
    message(STATUS "${FILE}")
endforeach()

add_library(menu SHARED ${MENUFILES})
target_link_libraries(menu PRIVATE sfml-graphics sfml-window sfml-system)
target_include_directories(menu PRIVATE 
${CMAKE_CURRENT_SOURCE_DIR} 
${CMAKE_SOURCE_DIR}/include
)

