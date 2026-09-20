# C++ 基础语法十六题：每个 .cpp 一个同名可执行文件，产物输出到 build 根目录
cmake_minimum_required(VERSION 3.16)
project(cpp_basics LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)          # 强制 C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 编译器不支持则直接报错，不允许降级
set(CMAKE_CXX_EXTENSIONS OFF)       # 用 -std=c++17 而非 gnu++17，严格标准写法

# 教学示例要求零警告：按 gcc/clang 的 -Wall -Wextra 水平编写
if(NOT MSVC)
    add_compile_options(-Wall -Wextra)
endif()

# 14_concurrency 需要 POSIX 线程；Threads::Threads 在 Linux 上链接 pthread
find_package(Threads REQUIRED)

# glob 收集本目录全部 .cpp，逐个生成同名 target（01_hello.cpp -> 01_hello）
file(GLOB BASICS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

foreach(src IN LISTS BASICS_SOURCES)
    get_filename_component(target_name "${src}" NAME_WE)
    add_executable(${target_name} "${src}")
    if(target_name STREQUAL "14_concurrency")
        target_link_libraries(${target_name} Threads::Threads)
    endif()
endforeach()
