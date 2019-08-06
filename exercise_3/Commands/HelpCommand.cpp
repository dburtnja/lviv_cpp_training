//
// Created by denys on 30.07.19.
//

#include "HelpCommand.hpp"

const std::string HelpCommand::NAME = "HELP";
const std::string HelpCommand::DESCRIPTION = "HELP: Type to print this message.\" << std::endl";

HelpCommand::HelpCommand(RecordsHandler &records_handler) : AbstractCommand(records_handler) {
}

const std::string &HelpCommand::get_name() const {
    return NAME;
}

const std::string &HelpCommand::get_info() const {
    return DESCRIPTION;
}

void HelpCommand::execute() {

}
