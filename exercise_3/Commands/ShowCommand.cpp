//
// Created by denys on 18.07.19.
//

#include "ShowCommand.hpp"
#include <sstream>
#include <iostream>

const std::string ShowCommand::COMMAND_NAME = "SHOW";
const std::string ShowCommand::DESCRIPTION = "SHOW [table_name [WHERE conditions]]: "
                                             "If table_name is present - print table or print all tables.";

namespace {
    auto print_records = [] (const std::string &table_name, const std::map<int, std::shared_ptr<IRecord>>& records) {
        if (!records.empty()) {
            std::cout << "Table " << table_name << ":" << std::endl;
            for (const auto& record : records) {
                std::cout << record.second->getPrettyPrinted() << std::endl;
            }
            std::cout << std::endl;
        }
    };
}

ShowCommand::ShowCommand(RecordsHandler &records_handler) : AbstractCommand(records_handler) {
}

void ShowCommand::execute() {
    std::string input_table_name;

    _arguments_stream >> input_table_name;
    if (input_table_name.empty() or input_table_name == "*") {
        for (const auto &table_name : _recordsHandler.get_tables()) {
            auto records = _recordsHandler.get_records(table_name);
            execute_with_condition(_arguments_stream, table_name, records, print_records);
        }
    } else {
        auto records = _recordsHandler.get_records(input_table_name);
        execute_with_condition(_arguments_stream, input_table_name, records, print_records);
    }
}

const std::string & ShowCommand::get_info() const {
    return DESCRIPTION;
}

const std::string &ShowCommand::get_name() const {
    return COMMAND_NAME;
}
