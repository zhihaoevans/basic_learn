cmake_minimum_required(VERSION 3.10)
project(cpp_examples)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executables for C++11 features
add_executable(auto_decltype auto_decltype.cpp)
add_executable(lambda_examples lambda.cpp)
add_executable(smart_pointers smart_pointers.cpp)
add_executable(rvalue_move rvalue_move.cpp)
add_executable(variadic_templates variadic_templates.cpp)
add_executable(range_based_for range_based_for.cpp)
add_executable(nullptr_example nullptr_example.cpp)
add_executable(enum_class enum_class.cpp)
add_executable(thread_example thread_example.cpp)
add_executable(initializer_lists initializer_lists.cpp)

# Add executables for basic C++ features
add_executable(basic_types basic_types.cpp)
add_executable(class_basics class_basics.cpp)
add_executable(template_basics template_basics.cpp)
add_executable(stl_examples stl_examples.cpp)

# Link pthread for thread examples
target_link_libraries(thread_example pthread) 
