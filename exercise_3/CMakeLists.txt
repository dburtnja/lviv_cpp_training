cmake_minimum_required(VERSION 3.14)
project(exercise_3)

set(CMAKE_CXX_STANDARD 17)


add_executable(exercise_3 main.cpp
        Model/IRecord.hpp Model/IPerson.hpp
        Model/Teacher.cpp Model/Teacher.hpp
        Model/Student.cpp Model/Student.hpp
        Model/Course.cpp Model/Course.hpp
        Model/Exam.cpp Model/Exam.hpp
        Model/RecordsHandler.cpp Model/RecordsHandler.hpp
        Commands/ICommand.hpp
        Commands/ShowCommand.cpp Commands/ShowCommand.hpp
        Model/AbstractRecord.cpp Model/AbstractRecord.hpp
        Commands/CommandsHandler.cpp Commands/CommandsHandler.hpp
        Model/Table.cpp Model/Table.hpp Commands/AbstractCommand.cpp Commands/AbstractCommand.hpp Commands/HelpCommand.cpp Commands/HelpCommand.hpp)

target_include_directories(exercise_3 PUBLIC Model Commands)

target_compile_options(exercise_3 PRIVATE -Wall -Wextra -Werror)
