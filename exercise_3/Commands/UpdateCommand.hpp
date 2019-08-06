//
// Created by denys on 01.08.19.
//

#pragma once


#include "AbstractCommand.hpp"

class UpdateCommand : public AbstractCommand {
private:
    static const std::string    COMMAND_NAME;
    static const std::string    DESCRIPTION;

public:
    explicit UpdateCommand(RecordsHandler &records_handler);
    const std::string & get_info() const override;
    const std::string & get_name() const override;

    void execute() override;
};



