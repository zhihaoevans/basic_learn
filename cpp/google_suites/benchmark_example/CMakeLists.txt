cmake_minimum_required(VERSION 3.20)
project(benchmark_example VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(
  googlebenchmark
  URL https://github.com/google/benchmark/archive/refs/tags/v1.8.3.zip
)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googlebenchmark)

find_package(Threads REQUIRED)

add_executable(bench_suite
  src/bench_suite.cc
)
target_link_libraries(bench_suite PRIVATE benchmark::benchmark Threads::Threads)

if(MSVC)
  target_compile_options(bench_suite PRIVATE /W4 /WX)
else()
  target_compile_options(bench_suite PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
