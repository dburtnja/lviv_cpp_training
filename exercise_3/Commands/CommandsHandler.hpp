//
// Created by denys on 24.07.19.
//

#pragma once


#include <string>
#include <vector>
#include <RecordsHandler.hpp>
#include "AbstractCommand.hpp"

class CommandsHandler {
public:
    explicit CommandsHandler(RecordsHandler &records_handler);
    std::string get_commands_info() const;
    void read_input(std::istream &istream);

private:
    std::vector<std::shared_ptr<AbstractCommand>> _commands;

    void _read_command(const std::string &command_line);
};



