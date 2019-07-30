//
// Created by denys on 30.07.19.
//

#pragma once


#include <RecordsHandler.hpp>
#include <sstream>
#include "ICommand.hpp"

class AbstractCommand : public ICommand {

protected:
    RecordsHandler &_recordsHandler;
    std::istringstream _arguments_stream;

public:
    AbstractCommand(RecordsHandler &recordsHandler);

    void read_command_arguments(const std::string &arguments);

    virtual const std::string & get_info() const = 0;
    virtual const std::string &get_name() const = 0;
};



