//
// Created by denys on 10.07.19.
//

#include <iostream>
#include <sstream>
#include "Course.hpp"

const std::string Course::MARKER = "C";

int Course::getId() const {
    return this->_id;
}

std::string Course::getFormatted() const {
    std::ostringstream  ostringstream;

    ostringstream << this->_id << "," << this->_name << "," << this->_teacher_id;
    return ostringstream.str();
}

Course::Course(std::istringstream &istringstream) {
    std::string buf;

    if (!std::getline(istringstream, buf, ','))
        throw std::invalid_argument("Wrong argument: " + istringstream.str());
    this->_id = std::stoi(buf);
    if (!std::getline(istringstream, this->_name, ','))
        throw std::invalid_argument("Wrong argument: " + istringstream.str());
    if (!std::getline(istringstream, buf, ','))
        throw std::invalid_argument("Wrong argument: " + istringstream.str());
    this->_teacher_id = std::stoi(buf);
}
