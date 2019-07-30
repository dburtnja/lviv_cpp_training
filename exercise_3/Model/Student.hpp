//
// Created by denys on 10.07.19.
//

#pragma once


#include <vector>
#include "IPerson.hpp"
#include "AbstractRecord.hpp"

class Student : public IPerson, public AbstractRecord {
private:
    int _id;
    std::string _name;
    std::vector<Parameter> _get_print_parameters() const override;


public:

    Student(std::istringstream &istringstream);
    int getId() const override;
    std::string getName() const override;
    std::string getFormatted() const override;
};



