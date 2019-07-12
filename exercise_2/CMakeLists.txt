cmake_minimum_required(VERSION 3.14)
project(exercise_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(exercise_2 main.cpp IRecord.hpp IPerson.hpp Teacher.cpp Teacher.hpp RecordsHandler.cpp RecordsHandler.hpp Student.cpp Student.hpp Course.cpp Course.hpp Exam.cpp Exam.hpp)

target_compile_options(exercise_2 PRIVATE -Wall -Wextra -Werror)