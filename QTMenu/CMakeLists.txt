#QTMenu/cmakeLists.txt
message(STATUS "Creating QT-based menu ...")


set (QTMENUFILES 
    "main.cpp"
    "menu.cpp" 
    "menuitem.cpp"
)
if(NOT QTMENUFILES)
    message(FATAL_ERROR "no files to compile in qtmenu")
endif()
message(STATUS "SOURCE FILES QTMENU:")
foreach(FILE IN LISTS QTMENUFILES)
    message(STATUS "${FILE}")
endforeach()

qt_standard_project_setup()
qt_add_executable(qtmenu
    ${QTMENUFILES}
)

target_link_libraries(qtmenu PRIVATE Qt6::Widgets)

set_target_properties(qtmenu PROPERTIES
    WIN32_EXECUTABLE ON
)

add_custom_command(TARGET qtmenu POST_BUILD #add qt dlls to output dir
    COMMAND "${CMAKE_PREFIX_PATH}/bin/windeployqt.exe"
            --debug
            --no-translations
            $<TARGET_FILE:qtmenu>
)