cmake_minimum_required(VERSION 3.20)
project(gtest_example VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_COVERAGE "Enable coverage instrumentation" OFF)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(calculator
  src/calculator.cc
)
target_include_directories(calculator PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if(MSVC)
  target_compile_options(calculator PRIVATE /W4 /WX)
else()
  target_compile_options(calculator PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

if(ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(calculator PRIVATE --coverage -O0)
  target_link_options(calculator PRIVATE --coverage)
endif()

enable_testing()
add_executable(calculator_tests
  tests/calculator_test.cc
)
target_link_libraries(calculator_tests PRIVATE
  GTest::gtest_main
  calculator
)

if(MSVC)
  target_compile_options(calculator_tests PRIVATE /W4 /WX)
else()
  target_compile_options(calculator_tests PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

include(GoogleTest)
gtest_discover_tests(calculator_tests)
