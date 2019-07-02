cmake_minimum_required(VERSION 3.13)
project(exercise_0)

set(CMAKE_CXX_STANDARD 17)

add_executable(exercise_0
        main.cpp)

target_compile_options(exercise_0 PRIVATE -Wall -Wextra -Werror)
