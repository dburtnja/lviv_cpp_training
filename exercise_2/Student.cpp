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
    _id = std::stoi(buf);
    if (!std::getline(istringstream, _name, ','))
        throw std::invalid_argument("Wrong argument: " + istringstream.str());
}

int Student::getId() const {
    return _id;
}

std::string Student::getFormatted() const {
    std::ostringstream  ostringstream;

    ostringstream << _id << "," << _name;
    return ostringstream.str();
}

std::string Student::getName() const {
    return _name;
}
