cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
message(STATUS "\n\ tests\n")

# -- get google test ---
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        f6f920d2ba09f3951af59045cd31c42e95bf127a 
  OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(googletest)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# --- find sources ---
set(TEST_SOURCES  physicalObjectTest.cpp ballTest.cpp
                )



if(NOT SRC_FILES)
    message(FATAL_ERROR "list of source files is empty")
endif()

if(NOT TEST_SOURCES)
    message(FATAL_ERROR "list of test files is empty")
endif()
#debug info
message(STATUS "tests:")
foreach(T ${TEST_SOURCES})
    message(STATUS "${T}")
endforeach()

# ---- create binary ----

add_executable(Tests  ${TEST_SOURCES}
                       ${SRC_FILES}
              )

target_link_libraries(Tests gtest_main sfml-graphics sfml-window sfml-system)
target_include_directories(Tests  PUBLIC
                              "${CMAKE_SOURCE_DIR}/src"
                             "${PROJECT_SOURCE_DIR}"
)

include(GoogleTest)
gtest_discover_tests(Tests )
