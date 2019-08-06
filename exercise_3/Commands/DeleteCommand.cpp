//
// Created by denys on 02.08.19.
//

#include <iostream>
#include "DeleteCommand.hpp"

const std::string DeleteCommand::COMMAND_NAME = "DELETE";
const std::string DeleteCommand::DESCRIPTION = "DELETE table_name WHERE conditions";

namespace {
    constexpr auto get_vector_of_keys = [] (const std::map<int, std::shared_ptr<IRecord>>& records) {
        std::vector<int> keys;

        keys.reserve(records.size());
        for (auto records_iterator : records)
            keys.push_back(records_iterator.first);
        return keys;
    };
}

DeleteCommand::DeleteCommand(RecordsHandler &records_handler) : AbstractCommand(records_handler) {

}

const std::string &DeleteCommand::get_info() const {
    return DESCRIPTION;
}

const std::string &DeleteCommand::get_name() const {
    return COMMAND_NAME;
}

void DeleteCommand::execute() {
    std::string input_table_name;
    RecordsHandler &recordsHandler = _recordsHandler;

    _arguments_stream >> input_table_name;
    auto update_records = [&recordsHandler]
            (const std::string &table_name, const std::map<int, std::shared_ptr<IRecord>>& records) {
        if (!records.empty()) {
            std::cout << "Deleting records from table: " << table_name << std::endl;
            for (const auto &record : records)
                std::cout << record.second->getPrettyPrinted() << std::endl;
            auto ids = get_vector_of_keys(records);
            recordsHandler.cleare_records(table_name, ids);
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
