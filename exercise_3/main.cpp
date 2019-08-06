
#include <iostream>
#include "Commands/ShowCommand.hpp"
#include "Commands/CommandsHandler.hpp"

static void start_execution(const std::string &file_name) {
    RecordsHandler  records_handler(file_name);
    CommandsHandler commands_handler(records_handler);

    commands_handler.read_input(std::cin);
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