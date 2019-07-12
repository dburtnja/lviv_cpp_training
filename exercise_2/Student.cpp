//
// Created by denys on 10.07.19.
//

#include <stdexcept>
#include <sstream>
#include "Student.hpp"

const std::string Student::MARKER = "S";

Student::Student(std::istringstream &istringstream) {
    std::string buf;

    if (!std::getline(istringstream, buf, ','))
        throw std::invalid_argument("Wrong argument: " + istringstream.str());
    this->_id = std::stoi(buf);
    if (!std::getline(istringstream, this->_name, ','))
        throw std::invalid_argument("Wrong argument: " + istringstream.str());
}

int Student::getId() const {
    return this->_id;
}

std::string Student::getFormatted() const {
    std::ostringstream  ostringstream;

    ostringstream << this->_id << "," << this->_name;
    return ostringstream.str();
}

std::string Student::getName() const {
    return this->_name;
}
