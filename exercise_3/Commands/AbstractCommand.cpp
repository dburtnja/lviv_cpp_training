//
// Created by denys on 30.07.19.
//

#include "AbstractCommand.hpp"

const std::string AbstractCommand::WHERE_CONDITION = "WHERE";

namespace {
    constexpr auto split_string = [] (const std::string &input, const std::string &delimeter) {
        std::list<std::string> tokens;
        std::size_t start = 0, end = 0;
        std::size_t delimeter_size = delimeter.size();

        do {
            end = input.find(delimeter, start);
            tokens.push_back(input.substr(start, end - start));
            start = end + delimeter_size;
        } while (end != std::string::npos);
        return tokens;
    };
}

AbstractCommand::AbstractCommand(RecordsHandler &recordsHandler) : _recordsHandler(recordsHandler) {
}

void AbstractCommand::read_command_arguments(const std::string &arguments) {
    _arguments_stream = std::istringstream(arguments);
}

void AbstractCommand::execute_with_condition(std::istringstream &condition, const std::string &table_name,
                                             const std::map<int, std::shared_ptr<IRecord>> &records,
                                             const std::function<void(std::string,
                                                                      std::map<int, std::shared_ptr<IRecord>>)> &executor) {
    std::string condition_name;
    auto temp_pos = condition.tellg();

    condition >> condition_name;
    if (condition_name.empty()) {
        executor(table_name, records);
    } else if (WHERE_CONDITION == condition_name) {
        std::map<int, std::shared_ptr<IRecord>> filtered_records;

        std::string conditions_str;
        std::getline(condition, conditions_str);
        auto conditions = _get_conditions_list(conditions_str);
        for (const auto &[id, record] : records) {
            if (record->match(conditions))
                filtered_records.insert({id, record});
        }
        executor(table_name, filtered_records);
    } else {
        throw std::invalid_argument("Unexpected command keyword: '" + condition_name + "'.");
    }
    condition.seekg(temp_pos);
}

std::vector<Condition> AbstractCommand::_get_conditions_list(const std::string &conditions_string) {
    std::vector<Condition> conditions;
    std::string buffer;
    auto conditons_list = split_string(conditions_string, "&&");

    conditions.reserve(conditons_list.size());
    for (const auto &condition_str : conditons_list) {
        std::istringstream condition_stream(condition_str);
        Condition condition;
        condition_stream >> condition.parameter_name >> condition.compare_sign >> condition.value;
        if (!condition_stream)
            throw std::invalid_argument("Invalid condition: '" + condition_str + "'.");
        conditions.push_back(condition);
    }
    return conditions;
}
