#include <iostream>
#include <fstream>
#include <sstream>
#include "ShowCommand.hpp"

const std::string EXIT = "EXIT";
const std::string HELP = "HELP";

namespace {
    auto show_help = [] {
        std::cout << "Available commands:" << std::endl;
        std::cout << "\tEXIT: Type to quit." << std::endl;
        std::cout << "\tHELP: Type to print this message." << std::endl;
        std::cout << std::endl;
        std::cout << "\tSHOW [table_name]: If table_name is present - print table or print all tables." << std::endl;
    };
}

static void select_command(const std::string &command, std::istringstream &istringstream, RecordsHandler &recordsHandler) {
    if (ShowCommand::can_execute(command)) {
        auto command_obj = ShowCommand(istringstream, recordsHandler);
        command_obj.execute();
    } else {
        std::cerr << "Invalid command: " + command << std::endl;
    }
}

static void start_execution(const std::string &file_name) {
    RecordsHandler  recordsHandler(file_name);
    std::string     command_str;

    show_help();
    while (std::cin) {
        try {
            std::getline(std::cin, command_str);
            if (command_str == EXIT)
                return;
            if (command_str == HELP) {
                show_help();
                continue;
            }
            std::istringstream  command_stream(command_str);
            command_stream >> command_str;
            if (command_stream and !command_stream.bad())
                select_command(command_str, command_stream, recordsHandler);
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

int main(int argc, char **argv) {
    if (argc == 2) {
        try {
            start_execution(argv[1]);
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    } else {
        std::cerr << "Usage: " << argv[0] << " <database dump file>" << std::endl;
        return EXIT_FAILURE;
    }
}