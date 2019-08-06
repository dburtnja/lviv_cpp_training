//
// Created by denys on 10.07.19.
//

#include <stdexcept>
#include <sstream>
#include "Student.hpp"

const std::string Student::ID = "ID";
const std::string Student::NAME = "Name";

Student::Student(std::istringstream &istringstream) {
    std::string buf;

    if (!std::getline(istringstream, buf, ','))
        throw std::invalid_argument("Wrong argument: " + istringstream.str());
    _id = str_to_int(buf);
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

std::vector<Parameter> Student::_get_print_parameters() const {
    return {
        {ID, std::to_string(_id)},
        {NAME, _name}
    };
}

bool Student::match(const std::vector<Condition> &conditions) const {
    return match_parameters(conditions, {{NAME, _name}}) and match_parameters(conditions, {{ID, _id}});
}

void Student::update(const std::string &key, const std::string &value) {
        if (NAME == key)
            _name = value;
}
