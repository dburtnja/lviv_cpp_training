//
// Created by denys on 18.07.19.
//

#pragma once


#include "ICommand.hpp"
#include "RecordsHandler.hpp"

class ShowCommand : public ICommand{

private:
    std::istringstream &_command;
    RecordsHandler &_recordsHandler;

public:
    static const std::string    COMMAND_NAME;

    static bool can_execute(const std::string &command_name) {
        return command_name == COMMAND_NAME;
    }

    ShowCommand(std::istringstream &command, RecordsHandler &recordsHandler);
    void execute() override;
};



