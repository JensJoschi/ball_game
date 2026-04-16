#QTMenu/cmakeLists.txt
message(STATUS "Creating QT-based menu ...")

set (QTMENUFILES 
    "menu.cpp" 
    "menuitem.cpp"
    "qtMenu.cpp"
)
if(NOT QTMENUFILES)
    message(FATAL_ERROR "no files to compile in qtmenu")
endif()
message(STATUS "SOURCE FILES QTMENU:")
foreach(FILE IN LISTS QTMENUFILES)
    message(STATUS "${FILE}")
endforeach()

qt_add_library(qtmenu STATIC ${QTMENUFILES})

target_link_libraries(qtmenu PRIVATE Qt6::Widgets)
target_include_directories(qtmenu PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
)


