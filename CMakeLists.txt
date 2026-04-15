cmake_minimum_required(VERSION 3.20)
project(ball VERSION 0.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_PREFIX_PATH "C:/Qt/6.7.3/msvc2022_64") 
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(FATAL_ERROR "This project requires a 64-bit build. Please configure accordingly.")
endif()

# --------- SFML -------------
if(NOT DEFINED SFML_ROOT)
    set (SFML_ROOT "C:/tools/SFML-2.6.2/") #prevents usage of sfml3, which is incompatible
endif()
set (SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")
set (SFML_BIN "${SFML_ROOT}/bin")
find_package(SFML 2.6.2 COMPONENTS graphics window system REQUIRED)
if(SFML_FOUND)
    message(STATUS "SFML found at ${SFML_DIR}")
else()
  message(FATAL_ERROR "SFML not found")
endif()
set_target_properties(sfml-graphics PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release)
set_target_properties(sfml-window   PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release)
set_target_properties(sfml-system   PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release)

# --------- output dir -------------
foreach(CONFIG_TYPE IN ITEMS Debug Release RelWithDebInfo MinSizeRel)
    string(TOUPPER ${CONFIG_TYPE} CONFIG_TYPE_UPPER)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG_TYPE_UPPER} ${CMAKE_SOURCE_DIR}/out/${CONFIG_TYPE})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIG_TYPE_UPPER} ${CMAKE_SOURCE_DIR}/out/${CONFIG_TYPE})
endforeach()

# --------- subdirectories -------------
add_subdirectory(menu)
add_subdirectory(game)
enable_testing()
add_subdirectory(tests) 
add_subdirectory(QTMenu)

# --------- main executable -------------
add_executable(ball main.cpp)
target_link_libraries(ball PRIVATE menu game sfml-graphics)

target_include_directories(ball PRIVATE 
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/menu/ #public header of menu, temporarily
    ${CMAKE_SOURCE_DIR}/game/ #public header of game, temporarily
) 

# --------- post-build -------------
add_custom_command(TARGET ball POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<$<CONFIG:Debug>:${SFML_BIN}/sfml-graphics-d-2.dll>
        $<$<CONFIG:Debug>:${SFML_BIN}/sfml-window-d-2.dll>
        $<$<CONFIG:Debug>:${SFML_BIN}/sfml-system-d-2.dll>
        $<$<CONFIG:Release>:${SFML_BIN}/sfml-graphics-2.dll>
        $<$<CONFIG:Release>:${SFML_BIN}/sfml-window-2.dll>
        $<$<CONFIG:Release>:${SFML_BIN}/sfml-system-2.dll>
        $<$<CONFIG:RelWithDebInfo>:${SFML_BIN}/sfml-graphics-2.dll>
        $<$<CONFIG:RelWithDebInfo>:${SFML_BIN}/sfml-window-2.dll>
        $<$<CONFIG:RelWithDebInfo>:${SFML_BIN}/sfml-system-2.dll>
        "C:/Windows/Fonts/arial.ttf"
        $<TARGET_FILE_DIR:ball>
)