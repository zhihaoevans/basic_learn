cmake_minimum_required(VERSION 3.20)
project(glog_example VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(
  glog
  URL https://github.com/google/glog/archive/refs/tags/v0.7.0.zip
)
set(WITH_GFLAGS OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glog)

add_executable(logging_example
  src/logging_example.cc
)
target_link_libraries(logging_example PRIVATE glog::glog)

if(MSVC)
  target_compile_options(logging_example PRIVATE /W4 /WX)
else()
  target_compile_options(logging_example PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
