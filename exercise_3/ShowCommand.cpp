//
// Created by denys on 18.07.19.
//

#include "ShowCommand.hpp"
#include <sstream>
#include <iostream>

const std::string ShowCommand::COMMAND_NAME = "SHOW";

namespace {
    auto print_records = [] (const std::string &table_name, const std::map<int, std::shared_ptr<IRecord>>& records) {
        if (!records.empty()) {
            std::cout << "Table " << table_name << ":" << std::endl;
            for (const auto& record : records)
                std::cout << record.second->getPrettyPrinted() << std::endl;
            std::cout << std::endl;
        }
    };
}

ShowCommand::ShowCommand(std::istringstream &command, RecordsHandler &recordsHandler) :
        _command(command), _recordsHandler(recordsHandler) {
}

void ShowCommand::execute() {
    std::string input_table_name;

    _command >> input_table_name;
    if (input_table_name.empty() or input_table_name == "*") {
        for (const auto &table_name : _recordsHandler.get_tables()) {
            auto records = _recordsHandler.get_records(table_name);
            print_records(table_name, records);
        }
    } else {
        auto records = _recordsHandler.get_records(input_table_name);
        print_records(input_table_name, records);
    }

}