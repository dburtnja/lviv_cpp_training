//
// Created by denys on 01.08.19.
//

#include <iostream>
#include "UpdateCommand.hpp"

const std::string UpdateCommand::COMMAND_NAME = "UPDATE";
const std::string UpdateCommand::DESCRIPTION = "UPDATE table_name column_name value [WHERE conditions]";


const std::string &UpdateCommand::get_info() const {
    return DESCRIPTION;
}

const std::string &UpdateCommand::get_name() const {
    return COMMAND_NAME;
}

void UpdateCommand::execute() {
    std::string input_table_name;
    std::string parameter_name;
    std::string new_value;

    _arguments_stream >> input_table_name;
    _arguments_stream >> parameter_name;
    _arguments_stream >> new_value;
    if (!_arguments_stream)
        throw std::invalid_argument("Invalid parameters: '" + _arguments_stream.str() + "'.");
    auto update_records = [parameter_name, new_value]
            (const std::string &table_name, const std::map<int, std::shared_ptr<IRecord>>& records) {
        std::cout << "Updating table: " << table_name << std::endl;
        if (!records.empty()) {
            for (const auto& record : records) {
                record.second->update(parameter_name, new_value);
                std::cout << record.second->getPrettyPrinted() << std::endl;
            }
        }
    };
    if (input_table_name.empty() or input_table_name == "*") {
        for (const auto &table_name : _recordsHandler.get_tables()) {
            auto records = _recordsHandler.get_records(table_name);
            execute_with_condition(_arguments_stream, table_name, records, update_records);
        }
    } else {
        auto records = _recordsHandler.get_records(input_table_name);
        execute_with_condition(_arguments_stream, input_table_name, records, update_records);
    }
}

UpdateCommand::UpdateCommand(RecordsHandler &records_handler) : AbstractCommand(records_handler) {
}
