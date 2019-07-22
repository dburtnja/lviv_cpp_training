//
// Created by denys on 10.07.19.
//

#pragma once


#include "IPerson.hpp"
#include "ARecord.hpp"

class Teacher : public IPerson, public ARecord {
private:
    int _id;
    std::string _name;

    std::list<std::pair<std::string, std::string>> _get_print_parameters() const override;

public:
    static const std::string MARKER;
    static const std::string RECORD_NAME;

    Teacher(std::istringstream &istringstream);
    int getId() const override;
    std::string getName() const override;
    std::string getFormatted() const override;
};



