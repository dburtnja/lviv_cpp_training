//
// Created by denys on 30.07.19.
//

#pragma once


#include "AbstractCommand.hpp"

class HelpCommand : public AbstractCommand {
private:
    const static std::string NAME;
    const static std::string DESCRIPTION;

public:
    explicit HelpCommand(RecordsHandler &records_handler);
    const std::string &get_name() const override;
    const std::string &get_info() const override;
    void execute() override;
};



