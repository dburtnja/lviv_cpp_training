//
// Created by denys on 10.07.19.
//

#include <stdexcept>
#include <sstream>
#include "Teacher.hpp"

const std::string Teacher::MARKER = "T";

Teacher::Teacher(std::istringstream &istringstream) {
    std::string buf;

    if (!std::getline(istringstream, buf, ','))
        throw std::invalid_argument("Wrong argument: " + istringstream.str());
    this->_id = std::stoi(buf);
    if (!std::getline(istringstream, this->_name, ','))
        throw std::invalid_argument("Wrong argument: " + istringstream.str());
}

int Teacher::getId() const {
    return this->_id;
}

std::string Teacher::getName() const {
    return this->_name;
}

std::string Teacher::getFormatted() const {
    std::ostringstream  ostringstream;

    ostringstream << this->_id << "," << this->_name;
    return ostringstream.str();
}
