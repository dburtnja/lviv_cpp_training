//
// Created by denys on 20.07.19.
//

#include <sstream>
#include <iostream>
#include "ARecord.hpp"

std::string ARecord::getPrettyPrinted() const {
    std::ostringstream  buffer;
    auto print_parameters = _get_print_parameters();
    auto &last_key = print_parameters.back().first;

    for (auto &[key, value] : print_parameters) {
        buffer << key << ": " << value;
        if (&key != &last_key)
            buffer << ", ";
    }
    return buffer.str();
}
