//
// Created by denys on 02.08.19.
//

#pragma once


#include <RecordsHandler.hpp>
#include "AbstractCommand.hpp"

class DeleteCommand : public AbstractCommand {
private:
    static const std::string    COMMAND_NAME;
    static const std::string    DESCRIPTION;

public:
    explicit DeleteCommand(RecordsHandler &records_handler);
    const std::string & get_info() const override;
    const std::string & get_name() const override;

    void execute() override;
};



