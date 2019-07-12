//
// Created by denys on 10.07.19.
//

#pragma once


#include "IPerson.hpp"

class Student : public IPerson {
private:
    int _id;
    std::string _name;


public:
    Student(std::istringstream &istringstream);
    int getId() const override;
    std::string getName() const override;
    std::string getFormatted() const override;
};



