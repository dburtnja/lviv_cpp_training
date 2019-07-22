cmake_minimum_required(VERSION 3.14)
project(exercise_3)

set(CMAKE_CXX_STANDARD 17)

add_executable(exercise_3 main.cpp
        IRecord.hpp IPerson.hpp
        Teacher.cpp Teacher.hpp
        Student.cpp Student.hpp
        Course.cpp Course.hpp
        Exam.cpp Exam.hpp
        RecordsHandler.cpp RecordsHandler.hpp
        ICommand.hpp
        ShowCommand.cpp ShowCommand.hpp ARecord.cpp ARecord.hpp)

target_compile_options(exercise_3 PRIVATE -Wall -Wextra -Werror)
