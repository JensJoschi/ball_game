cmake_minimum_required(VERSION 3.20)
project(ball VERSION 0.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#the following should prevent finding SFML 3 or at least error out, code is not compatible with SFML 3
set (SFML_DIR "C:/tools/SFML-2.6.2/lib/cmake/SFML")
find_package(SFML 2.6.2 COMPONENTS graphics window system REQUIRED)
if(SFML_FOUND)
  message(STATUS "SFML found")
else()
  message(FATAL_ERROR "SFML not found")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(menu)
#add_subdirectory(game)
enable_testing()
#add_subdirectory(tests) 

#add_executable(ball main.cpp)
#target_link_libraries(ball PUBLIC menu game)