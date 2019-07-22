cmake_minimum_required(VERSION 3.14)
project(exercise_1)

set(CMAKE_CXX_STANDARD 17)


add_executable(exercise_1 main.cpp Graph.hpp Node.cpp Node.hpp)

target_compile_options(exercise_1 PRIVATE -Wall -Wextra -Werror)
