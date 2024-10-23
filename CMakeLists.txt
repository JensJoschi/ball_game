cmake_minimum_required(VERSION 3.20)
project(ball VERSION 0.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
if(NOT SRC_FILES) #promoted to parent scope, so tests can use it
    message(FATAL_ERROR "list of source files is empty")
endif()
enable_testing()
#add_subdirectory(tests) 