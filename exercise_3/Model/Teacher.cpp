//
// Created by denys on 10.07.19.
//

#include <stdexcept>
#include <sstream>
#include "Teacher.hpp"

const std::string Teacher::ID = "ID";
const std::string Teacher::NAME = "Name";

Teacher::Teacher(std::istringstream &istringstream) {
    std::string buf;

    if (!std::getline(istringstream, buf, ','))
        throw std::invalid_argument("Wrong argument: " + istringstream.str());
    _id = std::stoi(buf);
    if (!std::getline(istringstream, _name, ','))
        throw std::invalid_argument("Wrong argument: " + istringstream.str());
}

int Teacher::getId() const {
    return _id;
}

std::string Teacher::getName() const {
    return _name;
}

std::string Teacher::getFormatted() const {
    std::ostringstream  ostringstream;

    ostringstream << _id << "," << _name;
    return ostringstream.str();
}

std::vector<Parameter> Teacher::_get_print_parameters() const {
    return {
        {ID, std::to_string(_id)},
        {NAME, _name}
    };
}

bool Teacher::match(const std::vector<Condition> &conditions) const {
    return match_parameters(conditions, {{NAME, _name}}) and match_parameters(conditions, {{ID, _id}});
}

void Teacher::update(const std::string &key, const std::string &value) {
    if (NAME == key)
        _name = value;
}
