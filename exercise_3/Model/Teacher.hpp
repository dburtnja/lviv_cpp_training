//
// Created by denys on 10.07.19.
//

#pragma once


#include "IPerson.hpp"
#include "AbstractRecord.hpp"

class Teacher : public IPerson, public AbstractRecord {
private:
    int _id;
    std::string _name;

    std::vector<Parameter> _get_print_parameters() const override;

public:

    Teacher(std::istringstream &istringstream);
    int getId() const override;
    std::string getName() const override;
    std::string getFormatted() const override;
};



