//
// Created by denys on 24.07.19.
//

#include <sstream>
#include <iostream>
#include "CommandsHandler.hpp"
#include "ShowCommand.hpp"
#include "HelpCommand.hpp"
#include "UpdateCommand.hpp"
#include "DeleteCommand.hpp"

const std::string EXIT = "EXIT";
const std::string HELP = "HELP";

CommandsHandler::CommandsHandler(RecordsHandler &records_handler) {
    _commands = {
            std::make_shared<ShowCommand>(records_handler),
            std::make_shared<UpdateCommand>(records_handler),
            std::make_shared<DeleteCommand>(records_handler)
    };
}

std::string CommandsHandler::get_commands_info() const {
    std::ostringstream ostringstream;

    ostringstream << "Available commands:" << std::endl;
    ostringstream << "\tEXIT: Type to quit." << std::endl;
    ostringstream << "\tHELP: Type to print this message." << std::endl;
    for (const auto &command : _commands)
        ostringstream << '\t' << command->get_info() << std::endl;
    return ostringstream.str();
}

void CommandsHandler::read_input(std::istream &istream) {
    std::string command_line;

    std::cout << get_commands_info();
    while (istream) {
        try {
            std::getline(istream, command_line);
            if (command_line.empty())
                continue ;
            if (istream.bad())
                throw std::invalid_argument("Bad input: '" + command_line + "'.");
            if (EXIT == command_line)
                return ;
            if (HELP == command_line) {
                std::cout << get_commands_info();
                continue;
            }
            _read_command(command_line);
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

void CommandsHandler::_read_command(const std::string &command_line) {
    std::istringstream  command_line_stream(command_line);
    std::string command_name;
    std::string command_arguments;

    command_line_stream >> command_name;
    std::getline(command_line_stream, command_arguments);
    for (auto &command : _commands) {
        if (command->get_name() == command_name) {
            command->read_command_arguments(command_arguments);
            command->execute();
            return;
        }
    }
    std::cerr << "No available command '" << command_name << "'" << std::endl;
    std::cerr << get_commands_info();
}

