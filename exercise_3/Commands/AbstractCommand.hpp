//
// Created by denys on 30.07.19.
//

#pragma once


#include <RecordsHandler.hpp>
#include <sstream>
#include "ICommand.hpp"

class AbstractCommand : public ICommand {

protected:
    static const std::string    WHERE_CONDITION;

    RecordsHandler &_recordsHandler;
    std::istringstream _arguments_stream;

    void execute_with_condition(std::istringstream &condition, const std::string &table_name,
                                const std::map<int, std::shared_ptr<IRecord>> &records,
                                const std::function<void(std::string,
                                                         std::map<int, std::shared_ptr<IRecord>>)> &executor);
    std::vector<Condition> _get_conditions_list(const std::string &conditions_string);

public:
    AbstractCommand(RecordsHandler &recordsHandler);

    void read_command_arguments(const std::string &arguments);

    virtual const std::string & get_info() const = 0;
    virtual const std::string &get_name() const = 0;
};
