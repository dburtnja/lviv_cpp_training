//
// Created by denys on 30.07.19.
//

#include "AbstractCommand.hpp"

AbstractCommand::AbstractCommand(RecordsHandler &recordsHandler) : _recordsHandler(recordsHandler) {
}

void AbstractCommand::read_command_arguments(const std::string &arguments) {
    _arguments_stream = std::istringstream(arguments);
}
