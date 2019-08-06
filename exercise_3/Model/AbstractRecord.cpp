//
// Created by denys on 20.07.19.
//

#include <sstream>
#include <iostream>
#include "AbstractRecord.hpp"

std::string AbstractRecord::getPrettyPrinted() const {
    std::ostringstream  buffer;
    const auto print_parameters = _get_print_parameters();
    auto &last_key = print_parameters.back().first;

    for (auto &[key, value] : print_parameters) {
        buffer << key << ": " << value;
        if (&key != &last_key)
            buffer << ", ";
    }
    return buffer.str();
}

int AbstractRecord::str_to_int(const std::string &input) {
    try {
        return std::stoi(input);
    } catch (std::exception &e) {
        throw std::invalid_argument("Could not convert '" + input + "' to integer.");
    }
}

bool AbstractRecord::match_parameters(const std::vector<Condition> &conditions,
                                      std::map<std::string, std::string> parameters) const {
    for (const auto & condition : conditions) {
        auto parameters_iterator = parameters.find(condition.parameter_name);
        if (parameters_iterator != parameters.end()) {
            if (!compare(parameters_iterator->second, condition.compare_sign, condition.value))
                return false;
        }
    }
    return true;
}

bool AbstractRecord::match_parameters(const std::vector<Condition> &conditions,
                                      std::map<std::string, int> parameters) const {
    for (const auto & condition : conditions) {
        auto parameters_iterator = parameters.find(condition.parameter_name);
        if (parameters_iterator != parameters.end()) {
            if (!compare(parameters_iterator->second, condition.compare_sign, std::stoi(condition.value))) {
                return false;
            }
        }
    }
    return true;
}
